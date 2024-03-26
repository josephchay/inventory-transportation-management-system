#pragma once

#include <vector>
#include <memory>
#include "Block.h"
#include "enums/BlockAttribute.h"

namespace blockchain {
    class Chain {
    public:
        /**
         * @brief A version number indicating which set of block validation rules to follow.
         */
        static const int VERSION;

        Chain(const int version, const std::string& bits = "ffff001f");

        Chain& addBlock(std::unique_ptr<Block> block);
        void display() const;
        void searchBlockByAttr(blockchain::enums::BlockAttribute attribute, const std::string& value) const;

        [[nodiscard]] int getNextBlockHeight() const;
        [[nodiscard]] std::string getLastBlockHash() const;
        [[nodiscard]] bool isEmpty() const;
        void addToRecord(const std::string& filename);

        [[nodiscard]] std::string getBits() const { return bits; }

    private:
        int version;
        std::string bits;

        std::vector<std::unique_ptr<Block>> blocks;
        void logBlockDetails(const Block& block, const std::string& filename);

        void displayBlockDetails(const std::unique_ptr<Block> &block) const;
    };
}
