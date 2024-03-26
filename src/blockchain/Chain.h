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

        Chain(const std::string dataFilePath, const int version, const std::string& bits = "ffff001f");

        Chain& addBlock(std::shared_ptr<Block> block);

        /**
         * @brief Temporarily hide a block from the blockchain.
         * The block still remain in the blockchain data record but will not be displayed
         *
         * @param block
         * @return
         */
        Chain& hideBlock(std::shared_ptr<Block> block);

        /**
         * @brief "Removes" a block from the blockchain by flagging it as invisible.
         * The block still remains in the blockchain data record due to immutability but will not be displayed.
         *
         * @param blockToHide
         * @return
         */
        Chain& removeBlock(std::shared_ptr<Block> blockToHide);
        void displayAll() const;
        void display(const std::vector<std::shared_ptr<Block>>& selectedBlocks) const;

        [[nodiscard]] std::vector<std::shared_ptr<Block>> searchBlockByAttr(blockchain::enums::BlockAttribute attribute, const std::string& value) const;
        [[nodiscard]] int getNextBlockHeight() const;
        [[nodiscard]] std::string getLastBlockHash() const;
        [[nodiscard]] bool isEmpty() const;
        void addToRecord();

        [[nodiscard]] std::string getBits() const { return bits; }

    private:
        const std::string dataFilePath;
        int version;
        std::string bits;

        std::vector<std::shared_ptr<Block>> blocks;
        void logBlockDetails(const Block& block, const std::string& filename);

        void displayBlockDetails(const std::shared_ptr<Block> &block) const;
        bool hasVisibleBlocks(const std::vector<std::shared_ptr<Block>>& blocks) const;
    };
}
