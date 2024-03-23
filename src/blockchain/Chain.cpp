#include "Chain.h"
#include "../filesystem/FileWriter.h"
#include <iostream>

namespace blockchain {
    Chain& Chain::addBlock(std::unique_ptr<Block> block) {
        block->setGenesis(block->getBlockNumber() == 0);
        blocks.push_back(std::move(block));

        return *this;
    }

    bool Chain::isEmpty() const {
        return blocks.empty();
    }

    void Chain::displayBlockchain() const {
        std::cout << "\n------------------- BLOCKCHAIN INFORMATION -------------------\n\n";
        for (const auto& block : blocks) {
            std::cout << "Block Type --> " << block->getBlockType() << "\n"
                      << "Block --> " << block->getBlockNumber() << (block->isGenesis() ? " (Genesis Block)" : "") << "\n"
                      << "Current Hash --> " << block->getCurrentBlockHash() << "\n"
                      << "Previous Hash --> " << block->getPreviousBlockHash() << "\n"
                      << "Timestamp --> " << block->getTimestamp() << "\n"
                      << "Information --> " << block->getInformationString() << "\n\n";
        }
        std::cout << "---------------- END OF BLOCKCHAIN INFORMATION ----------------\n\n";
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

    void Chain::logBlockDetails(const Block& block, const std::string& filename) {
        filesystem::FileWriter writer(filename);
        writer.writeLine("Block Type: " + block.getBlockType());
        writer.writeLine("Block Number: " + std::to_string(block.getBlockNumber()));
        writer.writeLine("Current Hash: " + block.getCurrentBlockHash());
        writer.writeLine("Previous Hash: " + block.getPreviousBlockHash());
        writer.writeLine("Timestamp: " + block.getTimestamp());
        writer.writeLine("Information: " + block.getInformationString());
        writer.writeLine(""); // Add an empty line for readability
    }

    void Chain::addToRecord(const std::string& filename) {
        if (!blocks.empty()) {
            const auto& block = blocks.back();
            logBlockDetails(*block, filename);
        }
    }
}
