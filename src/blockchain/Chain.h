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

        /**
         * @brief A string of bits that must be satisfied by the hash of a block.
         *
         * @param dataFilePath
         * @param version
         * @param bits
         */
        Chain(const std::string dataFilePath, const int version, const std::string& bits = "ffff001f");

        /**
         * @brief Add a block to the blockchain.
         *
         * @param block
         * @return
         */
        Chain& addBlock(std::shared_ptr<Block> block);

        /**
         * @brief Edit a block in the blockchain.
         *
         * @param block
         * @param info
         * @return
         */
        Chain& editBlock(std::shared_ptr<Block> block, const std::string& info);

        /**
         * @brief "Removes" a block from the blockchain by flagging it as invisible.
         *
         * @param block
         * @param info
         * @return
         */
        Chain& hardEditBlock(std::shared_ptr<Block> block, const std::string& info);

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
         * @param block
         * @return
         */
        Chain& hardHideBlock(std::shared_ptr<Block> block);

        /**
         * @brief Mine a block in the blockchain.
         *
         * @param block
         * @return
         */
        Chain& mineBlock(std::shared_ptr<Block> block);

        /**
         * @brief Display all blocks in the blockchain.
         */
        void displayAll() const;

        /**
         * @brief Display selected blocks in the blockchain.
         *
         * @param selectedBlocks
         */
        void display(const std::vector<std::shared_ptr<Block>>& selectedBlocks) const;

        /**
         * @brief Search for a block in the blockchain by attribute.
         *
         * @param attribute
         * @param value
         * @return
         */
        [[nodiscard]] std::vector<std::shared_ptr<Block>> searchBlockByAttr(blockchain::enums::BlockAttribute attribute, const std::string& value) const;

        /**
         * @brief Get the next block height in the blockchain.
         *
         * @return
         */
        [[nodiscard]] int getNextBlockHeight() const;

        /**
         * @brief Get the last block hash in the blockchain.
         *
         * @return
         */
        [[nodiscard]] std::string getLastBlockHash() const;

        /**
         * @brief Get a block by its height in the chain.
         *
         * @param height
         * @return
         */
        std::shared_ptr<Block> getBlockByHeight(int height);

        /**
         * @brief Get the last block in the chain.
         *
         * @return
         */
        [[nodiscard]] bool isEmpty() const;

        /**
         * @brief Get the last block in the chain.
         *
         * @return
         */
        void addToRecord();

        [[nodiscard]] std::string getBits() const { return bits; }

    private:
        /**
         * @brief The path to the blockchain data file.
         */
        const std::string dataFilePath;

        /**
         * @brief The version number indicating which set of block validation rules to follow.
         */
        int version;

        /**
         * @brief A string of bits that must be satisfied by the hash of a block.
         */
        std::string bits;

        /**
         * @brief The list of blocks in the blockchain.
         */
        std::vector<std::shared_ptr<Block>> blocks;

        /**
         * @brief The list of blocks in the blockchain.
         * @param block
         * @param filename
         */
        void logBlockDetails(const Block& block, const std::string& filename);

        /**
         * @brief Display the details of a block.
         *
         * @param block
         */
        void displayBlockDetails(const std::shared_ptr<Block> &block) const;

        /**
         * @brief Check if the blockchain has any visible blocks.
         *
         * @param blocks
         * @return
         */
        [[nodiscard]] bool hasVisibleBlocks(const std::vector<std::shared_ptr<Block>>& blocks) const;
    };
}
