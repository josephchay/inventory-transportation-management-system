#pragma once

#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace blockchain {
    class Block {
    public:
        [[nodiscard]] std::string getBlockType() const;
        [[nodiscard]] int getBlockNumber() const;
        [[nodiscard]] std::string getCurrentBlockHash() const;
        [[nodiscard]] std::string getPreviousBlockHash() const;
        [[nodiscard]] std::string getTimestamp() const;
        [[nodiscard]] std::string getInformationString() const;

    protected:
        std::string blockType;

        Block(int blockNumber, const std::string& previousBlockHash, const std::string& information, const std::string& blockType);

        std::string formatTimestamp(std::time_t time) const;

        /**
         * Generates a random hash string using a high-quality random number generator.
         * This function creates a string composed of randomly selected alphanumeric characters (a-z, A-Z, 0-9).
         * The length of the generated hash can be specified by the caller.
         *
         * @param hashLength The desired length of the generated hash string. Default is 20 characters.
         * @return A string containing a randomly generated hash of the specified length.
         *
         * Example usage:
         * std::string myHash = generateRandomHash(20); // Generates a random hash string of 20 characters.
         */
        std::string generateRandomHash(size_t hashLength = 20) const;

    private:
        int blockNumber;
        std::string currentBlockHash;
        std::string previousBlockHash;
        std::string timestamp;
        std::string informationString;
        Block* nextBlock;
    };
} // namespace blockchain
