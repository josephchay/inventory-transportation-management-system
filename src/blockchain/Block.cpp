#include <ctime>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "Block.h"

namespace blockchain {
    Block::Block(int blockNumber, const std::string& previousBlockHash, const std::string& information, const std::string& blockType)
            : blockNumber(blockNumber), previousBlockHash(previousBlockHash), informationString(information), blockType(blockType) {
        // Initialize timestamp with the current date and time
        std::time_t currentTime = std::time(nullptr);
        this->timestamp = formatTimestamp(currentTime);

        // Generate a current block hash
        this->currentBlockHash = generateRandomHash(60);

        // For a genesis block, set the previous block hash to its own hash
        if (previousBlockHash.empty() || previousBlockHash == "0") {
            this->previousBlockHash = this->currentBlockHash;
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
    int Block::getBlockNumber() const { return blockNumber; }
    std::string Block::getCurrentBlockHash() const { return currentBlockHash; }
    std::string Block::getPreviousBlockHash() const { return previousBlockHash; }
    std::string Block::getTimestamp() const { return timestamp; }
    std::string Block::getInformationString() const { return informationString; }
    bool Block::isGenesis() const { return genesis; }
} // namespace blockchain
