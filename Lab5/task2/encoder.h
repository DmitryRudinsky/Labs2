#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
#include <string>
#include <cstddef>

class Encoder {
private:
    std::vector<std::byte> key;

    void keyScheduling(std::vector<std::byte>& S);
    void pseudoRandomGeneration(const std::vector<std::byte>& S, std::vector<std::byte>& data);

public:
    explicit Encoder(const std::vector<std::byte>& encryption_key);
    void setKey(const std::vector<std::byte>& new_key);
    void encode(const std::string& input_file, const std::string& output_file, bool is_encrypt);
};

#endif // ENCODER_H
