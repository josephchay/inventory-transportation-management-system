#pragma once

#include <vector>
#include <memory>
#include "Block.h"

namespace blockchain {
    class Chain {
    public:
        void addBlock(std::unique_ptr<Block> block);
        void displayBlockchain() const;
        int getNextBlockNumber() const;
        std::string getLastBlockHash() const;

    private:
        std::vector<std::unique_ptr<Block>> blocks;
    };
}
