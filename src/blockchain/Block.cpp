#include <random>
#include "Block.h"

namespace blockchain {
    Block::Block(int height, const std::string& previousHash, const std::string& information, const std::string& blockType, int nonce, const std::string& currentHash)
            : height(height), blockType(blockType), header(information, nonce, currentHash, previousHash) {
    }

    void Block::setGenesis(bool genesisValue) {
        genesis = genesisValue;
    }

    // Getter methods
    std::string Block::getType() const { return blockType; }
    int Block::getHeight() const { return height; }
    int Block::getNonce() const { return header.getNonce(); }
    std::string Block::getCurrentHash() const { return header.getHash(); }
    std::string Block::getPrevHash() const { return header.getPrevHash(); }
    time_t Block::getTimestamp() const { return header.getTimestamp(); }
    std::string Block::getFormattedTimestamp() const { return header.getFormattedTimestamp(); }
    std::string Block::getInformationString() const { return header.getInformationString(); }
    bool Block::isGenesis() const { return genesis; }
} // namespace blockchain
