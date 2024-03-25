#include <random>
#include "Block.h"

namespace blockchain {
    Block::Block(const int version, const std::string bits, int height, const std::string& previousHash, const std::string& information, const std::string& blockType, int nonce, const std::string& currentHash)
            : height(height), type(blockType), header(version, bits, information, nonce, currentHash, previousHash) {
    }

    void Block::setGenesis(bool genesisValue) {
        genesis = genesisValue;
    }

    // Getter methods
    std::string Block::getType() const { return type; }
    int Block::getHeight() const { return height; }
    int Block::getNonce() const { return header.getNonce(); }
    std::string Block::getCurrentHash() const { return header.getHash(); }
    std::string Block::getPrevHash() const { return header.getPrevHash(); }
    std::string Block::getMerkleRoot() const { return header.getMerkleRoot(); }
    time_t Block::getTimestamp() const { return header.getTimestamp(); }
    std::string Block::getFormattedTimestamp() const { return header.getFormattedTimestamp(); }
    std::string Block::getInformationString() const { return header.getInformationString(); }
    bool Block::isGenesis() const { return genesis; }
} // namespace blockchain
