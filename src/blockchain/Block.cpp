#include <ctime>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "Block.h"

namespace blockchain {
    Block::Block(int number, const std::string& previousHash, const std::string& information, const std::string& blockType, const std::string& currentHash)
            : number(number), previousHash(previousHash), informationString(information), blockType(blockType), currentHash(currentHash) {
        // Initialize timestamp with the current date and time
        std::time_t currentTime = std::time(nullptr);
        this->timestamp = formatTimestamp(currentTime);

        // Generate a current block hash
        if (this->currentHash.empty()) {
            this->currentHash = generateRandomHash(60);
        } else {
            this->currentHash = currentHash;
        }

        // For a genesis block, set the previous block hash to its own hash
        if (previousHash.empty() || previousHash == "0") {
            this->previousHash = this->currentHash;
        }
    }

    std::string Block::generateRandomHash(size_t hashLength) const {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::string randHash;
        randHash.reserve(hashLength);

        // Use a high-quality random number generator
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<> distribution(0, chars.size() - 1);

        // Generate a random hash
        std::generate_n(std::back_inserter(randHash), hashLength, [&]() { return chars[distribution(generator)]; });

        return randHash;
    }

    // Format the timestamp for the block
    std::string Block::formatTimestamp(std::time_t time) const {
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void Block::setGenesis(bool genesisValue) {
        genesis = genesisValue;
    }

    // Getter methods
    std::string Block::getBlockType() const { return blockType; }
    int Block::getBlockNumber() const { return number; }
    std::string Block::getCurrentBlockHash() const { return currentHash; }
    std::string Block::getPreviousBlockHash() const { return previousHash; }
    std::string Block::getTimestamp() const { return timestamp; }
    std::string Block::getInformationString() const { return informationString; }
    bool Block::isGenesis() const { return genesis; }
} // namespace blockchain
