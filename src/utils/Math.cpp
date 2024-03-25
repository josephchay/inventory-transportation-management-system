#include "Math.h"
#include <stdexcept>
#include <algorithm>
#include <array> // Include this for std::array

namespace utils {
    std::vector<uint8_t> Math::intToLittleEndian(uint32_t value, size_t length) {
        std::vector<uint8_t> result;

        for (size_t i = 0; i < length; ++i) {
            result.push_back(static_cast<uint8_t>((value >> (i * 8)) & 0xFF));
        }

        return result;
    }

    uint32_t Math::littleEndianToInt(const std::vector<uint8_t>& bytes) {
        if (bytes.size() < 4) {
            throw std::invalid_argument("Byte array is too short to represent a 32-bit integer.");
        }
        return static_cast<uint32_t>(bytes[0]) |
               static_cast<uint32_t>(bytes[1]) << 8 |
               static_cast<uint32_t>(bytes[2]) << 16 |
               static_cast<uint32_t>(bytes[3]) << 24;
    }

    std::string Math::bytesToHex(const std::vector<uint8_t>& bytes) {
        static const char hexDigits[] = "0123456789abcdef";  // Hexadecimal digits

        std::string hexStr;
        hexStr.reserve(bytes.size() * 2);  // Each byte will be represented by two hex digits

        for (uint8_t byte : bytes) {
            hexStr.push_back(hexDigits[byte >> 4]);  // Append high nibble (4 bits)
            hexStr.push_back(hexDigits[byte & 0x0F]);  // Append low nibble
        }

        return hexStr;
    }

    std::vector<uint8_t> Math::hexToBytes(const std::string& hex) {
        std::vector<uint8_t> bytes;

        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16));
            bytes.push_back(byte);
        }

        return bytes;
    }

    std::vector<uint8_t> Math::targetToBits(const std::array<std::uint8_t, 32>& target) {
        // Find the first non-zero byte
        auto it = std::find_if(target.begin(), target.end(), [](uint8_t byte) { return byte != 0; });

        // Prepare the output vector
        std::vector<uint8_t> bits;

        int exponent;
        if (it != target.end() && *it > 0x7F) {
            // If the first byte is greater than 0x7F, adjust the exponent and prepend a 0x00
            exponent = 32 - std::distance(target.begin(), it) + 1;
            bits.push_back(0x00);
            bits.push_back(*it);
            if (std::distance(it, target.end()) > 1) {
                bits.push_back(*(it + 1));
            }
        } else {
            // Otherwise, use the available bytes directly
            exponent = 32 - std::distance(target.begin(), it);
            bits.insert(bits.end(), it, it + std::min(static_cast<size_t>(std::distance(it, target.end())), size_t(3)));
        }

        // Reverse the coefficient bytes and append the exponent
        std::reverse(bits.begin(), bits.end());
        bits.push_back(static_cast<uint8_t>(exponent));

        return bits;
    }

    unsigned int Math::targetArrayToInt(const std::array<std::uint8_t, 32>& targetArray) {
        if (targetArray.size() < 4) {
            // Handle error or return a default value
            return 0;
        }

        unsigned int result = 0;
        // Assume targetArray is big-endian, and we're only considering the first 4 bytes for simplicity
        for (int i = 0; i < 4; i++) {
            result <<= 8;
            result |= targetArray[i];
        }

        return result;
    }
}
