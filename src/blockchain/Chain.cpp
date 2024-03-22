#include "Chain.h"
#include <iostream>

namespace blockchain {
    void Chain::addBlock(std::unique_ptr<Block> block) {
        blocks.push_back(std::move(block));
    }

    void Chain::displayBlockchain() const {
        std::cout << "\n----------- Blockchain Information: -----------\n\n";
        for (const auto& block : blocks) {
            std::cout << "Block Type --> " << block->getBlockType() << "\n"
                      << "Block --> " << block->getBlockNumber() << "\n"
                      << "Current Hash --> " << block->getCurrentBlockHash() << "\n"
                      << "Previous Hash --> " << block->getPreviousBlockHash() << "\n"
                      << "Timestamp --> " << block->getTimestamp() << "\n"
                      << "Information --> " << block->getInformationString() << "\n\n";
        }
        std::cout << "----------- End of Blockchain Information -----------\n\n";
    }

    int Chain::getNextBlockNumber() const {
        return static_cast<int>(blocks.size());
    }

    std::string Chain::getLastBlockHash() const {
        if (!blocks.empty()) {
            return blocks.back()->getCurrentBlockHash();
        }
        return "0"; // Return a default hash for the genesis block
    }
}
