#include <iostream>
#include "encoder.h"

int main() {
    try {
        std::vector<std::byte> key = { std::byte(0x12), std::byte(0x34), std::byte(0x56), std::byte(0x78) };

        Encoder encoder(key);

        encoder.encode("input.txt", "encrypted.txt", true);
        std::cout << "File encrypted successfully!" << std::endl;

        encoder.encode("encrypted.txt", "decrypted.txt", false);
        std::cout << "File decrypted successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
