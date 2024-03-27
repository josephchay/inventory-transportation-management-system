#include <random>
#include "Block.h"

namespace blockchain {
    Block::Block(const int version, const std::string bits, int height, const std::string& previousHash, const std::string& information, blockchain::enums::BlockType type, int nonce, const std::string& currentHash, bool visible)
            : height(height), type(type), header(type, version, bits, information, nonce, currentHash, previousHash), visible(visible) {
    }

    // Getter methods
    blockchain::enums::BlockType Block::getType() const { return type; }
    int Block::getHeight() const { return height; }
    int Block::getNonce() const { return header.getNonce(); }
    std::string Block::getHash() const { return header.getHash(); }
    std::string Block::getPrevHash() const { return header.getPrevHash(); }
    std::string Block::getMerkleRoot() const { return header.getMerkleRoot(); }
    time_t Block::getTimestamp() const { return header.getTimestamp(); }
    std::string Block::getFormattedTimestamp() const { return header.getFormattedTimestamp(); }
    std::string Block::getInformationString() const { return header.getInformationString(); }
    bool Block::isGenesis() const { return genesis; }
    bool Block::isVisible() const { return visible; }

    // Setter methods
    void Block::setGenesis(bool genesisValue) { genesis = genesisValue; }
    void Block::setVisible(bool visibility) { visible = visibility; }
    void Block::setInformationString(const std::string& information) { header.setInformationString(information); }
} // namespace blockchain
