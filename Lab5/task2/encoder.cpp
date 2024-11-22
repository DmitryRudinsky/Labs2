#include "encoder.h"
#include <fstream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <unordered_map>

const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static const std::unordered_map<char, unsigned char> base64_reverse = []() {
    std::unordered_map<char, unsigned char> table;
    for (size_t i = 0; i < sizeof(base64_chars) - 1; ++i) {
        table[base64_chars[i]] = static_cast<unsigned char>(i);
    }
    return table;
}();

std::string encodeBase64(const std::vector<std::byte>& data) {
    std::ostringstream result;
    size_t i = 0;
    size_t len = data.size();
    unsigned char array3[3], array4[4];

    for (size_t pos = 0; pos < len; ++pos) {
        array3[i++] = static_cast<unsigned char>(data[pos]);
        if (i == 3) {
            array4[0] = (array3[0] & 0xfc) >> 2;
            array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
            array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
            array4[3] = array3[2] & 0x3f;

            for (i = 0; i < 4; i++) {
                result << base64_chars[array4[i]];
            }
            i = 0;
        }
    }

    if (i > 0) {
        for (size_t j = i; j < 3; j++) {
            array3[j] = '\0';
        }

        array4[0] = (array3[0] & 0xfc) >> 2;
        array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
        array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
        array4[3] = array3[2] & 0x3f;

        for (size_t j = 0; j < i + 1; j++) {
            result << base64_chars[array4[j]];
        }

        while (i++ < 3) {
            result << '=';
        }
    }

    return result.str();
}

std::vector<std::byte> decodeBase64(const std::string& encoded) {
    std::vector<std::byte> result;
    size_t len = encoded.size();
    size_t i = 0;
    unsigned char array4[4], array3[3];

    while (len-- && encoded[i] != '=' && base64_reverse.count(encoded[i])) {
        array4[i % 4] = base64_reverse.at(encoded[i]);
        if ((i % 4) == 3) {
            array3[0] = (array4[0] << 2) + ((array4[1] & 0x30) >> 4);
            array3[1] = ((array4[1] & 0xf) << 4) + ((array4[2] & 0x3c) >> 2);
            array3[2] = ((array4[2] & 0x3) << 6) + array4[3];

            result.push_back(static_cast<std::byte>(array3[0]));
            result.push_back(static_cast<std::byte>(array3[1]));
            result.push_back(static_cast<std::byte>(array3[2]));
        }
        ++i;
    }

    if ((i % 4) > 0) {
        for (size_t j = i % 4; j < 4; j++) {
            array4[j] = 0;
        }

        array3[0] = (array4[0] << 2) + ((array4[1] & 0x30) >> 4);
        array3[1] = ((array4[1] & 0xf) << 4) + ((array4[2] & 0x3c) >> 2);

        result.push_back(static_cast<std::byte>(array3[0]));
        if ((i % 4) == 3) {
            result.push_back(static_cast<std::byte>(array3[1]));
        }
    }

    return result;
}

Encoder::Encoder(const std::vector<std::byte>& encryption_key) : key(encryption_key) {
    if (key.empty()) {
        throw std::invalid_argument("Encryption key cannot be empty.");
    }
}

void Encoder::setKey(const std::vector<std::byte>& new_key) {
    if (new_key.empty()) {
        throw std::invalid_argument("New key cannot be empty.");
    }
    key = new_key;
}

void Encoder::keyScheduling(std::vector<std::byte>& S) {
    size_t key_length = key.size();
    for (size_t i = 0; i < 256; ++i) {
        S[i] = static_cast<std::byte>(i);
    }
    size_t j = 0;
    for (size_t i = 0; i < 256; ++i) {
        j = (j + static_cast<size_t>(S[i]) + static_cast<size_t>(key[i % key_length])) % 256;
        std::swap(S[i], S[j]);
    }
}

void Encoder::pseudoRandomGeneration(const std::vector<std::byte>& S, std::vector<std::byte>& data) {
    size_t i = 0, j = 0;
    std::vector<std::byte> S_copy = S;

    for (size_t k = 0; k < data.size(); ++k) {
        i = (i + 1) % 256;
        j = (j + static_cast<size_t>(S_copy[i])) % 256;
        std::swap(S_copy[i], S_copy[j]);
        std::byte key_byte = S_copy[(static_cast<size_t>(S_copy[i]) + static_cast<size_t>(S_copy[j])) % 256];
        data[k] ^= key_byte;
    }
}

void Encoder::encode(const std::string& input_file, const std::string& output_file, bool is_encrypt) {
    std::ifstream input(input_file, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open input file: " + input_file);
    }

    std::string input_content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();

    std::vector<std::byte> input_data;

    if (is_encrypt) {
        std::transform(
            input_content.begin(),
            input_content.end(),
            std::back_inserter(input_data),
            [](char c) { return static_cast<std::byte>(c); }
        );
    } else {
        input_data = decodeBase64(input_content);
    }

    if (input_data.empty()) {
        throw std::runtime_error("Input file is empty or decoding failed: " + input_file);
    }

    std::vector<std::byte> S(256);
    keyScheduling(S);
    pseudoRandomGeneration(S, input_data);

    if (is_encrypt) {
        std::string encoded_data = encodeBase64(input_data);

        std::ofstream output(output_file, std::ios::binary);
        if (!output.is_open()) {
            throw std::runtime_error("Failed to open output file: " + output_file);
        }

        output << encoded_data;
        output.close();
    } else {
        std::ofstream output(output_file, std::ios::binary);
        if (!output.is_open()) {
            throw std::runtime_error("Failed to open output file: " + output_file);
        }

        output.write(reinterpret_cast<const char*>(input_data.data()), input_data.size());
        output.close();
    }
}
