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
    BlockHeader& Block::getHeader() { return header; }
    BlockHeader Block::getHeader() const { return header; }
    bool Block::isGenesis() const { return genesis; }
    bool Block::isVisible() const { return visible; }

    // Setter methods
    void Block::setGenesis(bool genesisValue) { genesis = genesisValue; }
    void Block::setVisible(bool visibility) { visible = visibility; }
    void Block::setInformationString(const std::string& information) { header.setInformationString(information); }
} // namespace blockchain
