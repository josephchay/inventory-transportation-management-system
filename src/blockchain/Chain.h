#pragma once

#include <vector>
#include <memory>
#include "Block.h"

namespace blockchain {
    class Chain {
    public:
        Chain& addBlock(std::unique_ptr<Block> block);
        void displayBlockchain() const;
        [[nodiscard]] int getNextBlockNumber() const;
        [[nodiscard]] std::string getLastBlockHash() const;
        [[nodiscard]] bool isEmpty() const;
        void addToRecord(const std::string& filename);

    private:
        std::vector<std::unique_ptr<Block>> blocks;
        static void logBlockDetails(const Block& block, const std::string& filename);
    };
}
