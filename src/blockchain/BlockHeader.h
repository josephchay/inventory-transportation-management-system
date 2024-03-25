#pragma once

#include <string>
#include <ctime>
#include <cstdint>
#include <vector>

namespace blockchain {
    class BlockHeader {
    public:
        /**
         * @brief A version number indicating which set of block validation rules to follow.
         */
        static const int VERSION;

        BlockHeader(const std::string& informationString, int nonce = 0, const std::string& hash = "", const std::string& previousHash = "");

        [[nodiscard]] std::string getHash() const;
        [[nodiscard]] std::string getPrevHash() const;
        [[nodiscard]] std::string getMerkleRoot() const;
        [[nodiscard]] time_t getTimestamp() const;
        [[nodiscard]] std::string getFormattedTimestamp() const;
        [[nodiscard]] std::string getBits() const;
        [[nodiscard]] std::string getInformationString() const;
        [[nodiscard]] int getNonce() const;

    protected:
        std::string hash;
        std::string previousHash;
        std::string merkleRoot;
        time_t timestamp;
        std::string formattedTimestamp;
        std::string bits; // Difficulty target bits
        std::string informationString;
        int nonce;

        std::string mine();
    };
} // namespace blockchain