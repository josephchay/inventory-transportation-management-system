#include "Chain.h"
#include "../filesystem/FileWriter.h"
#include <iostream>

namespace blockchain {
    const int Chain::VERSION = 1;

    Chain::Chain(const std::string& bits) : bits(bits) {}

    Chain& Chain::addBlock(std::unique_ptr<Block> block) {
        block->setGenesis(block->getHeight() == 0);
        blocks.push_back(std::move(block));

        return *this;
    }

    bool Chain::isEmpty() const {
        return blocks.empty();
    }

    void Chain::displayBlockchain() const {
        std::cout << std::endl << "------------------------------- BLOCKCHAIN -------------------------------" << std::endl << std::endl;
        for (const auto& block : blocks) {
            std::cout << "Block Type --> " << blockchain::enums::toString(block->getType()) << std::endl
                      << "Height --> " << block->getHeight() << (block->isGenesis() ? " (Genesis Block)" : "") << std::endl
                      << "Version --> " << VERSION << std::endl
                      << "Nonce --> " << block->getNonce() << std::endl
                      << "Current Hash --> " << block->getCurrentHash() << std::endl
                      << "Previous Hash --> " << block->getPrevHash() << std::endl
                      << "Merkle Root --> " << block->getMerkleRoot() << std::endl
                      << "Timestamp --> " << block->getTimestamp() << " (" + block->getFormattedTimestamp() + ")" << std::endl
                      << "Bits --> " << bits << std::endl
                      << "Information --> " << "[ " << block->getInformationString() << " ]" << std::endl << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------" << std::endl << std::endl;
    }

    int Chain::getNextBlockHeight() const {
        return static_cast<int>(blocks.size());
    }

    std::string Chain::getLastBlockHash() const {
        if (!blocks.empty()) {
            return blocks.back()->getCurrentHash();
        }
        return "0"; // Return a default hash for the genesis block
    }

    void Chain::logBlockDetails(const Block& block, const std::string& filename) {
        filesystem::FileWriter writer(filename);

        writer.writeLine("Block Type: " + blockchain::enums::toString(block.getType()));
        writer.writeLine("Height: " + std::to_string(block.getHeight()));
        writer.writeLine("Version: " + std::to_string(VERSION));
        writer.writeLine("Nonce: " + std::to_string(block.getNonce()));
        writer.writeLine("Current Hash: " + block.getCurrentHash());
        writer.writeLine("Previous Hash: " + block.getPrevHash());
        writer.writeLine("Merkle Root: " + block.getMerkleRoot());
        writer.writeLine("Timestamp: " + std::to_string(block.getTimestamp()));
        writer.writeLine("Bits: " + bits);
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
