#ifndef MATH_H
#define MATH_H

#include <cstdint>
#include <vector>
#include <string>
#include <vector>
#include <stdexcept>
#include <climits>

namespace utils {
    class Math {
    public:
        static std::vector<uint8_t> intToLittleEndian(uint32_t value, size_t length);
        static uint32_t littleEndianToInt(const std::vector<uint8_t>& bytes);
        static std::string bytesToHex(const std::vector<uint8_t>& bytes);
        static std::vector<uint8_t> hexToBytes(const std::string& hex);
        static std::vector<uint8_t> targetToBits(const std::array<std::uint8_t, 32>& target);
        static unsigned int targetArrayToInt(const std::array<std::uint8_t, 32>& targetArray);
    };
}

#endif // MATH_H
