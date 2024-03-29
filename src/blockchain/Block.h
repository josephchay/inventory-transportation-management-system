#pragma once

#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <memory>
#include "BlockHeader.h"
#include "enums/BlockType.h"

namespace blockchain {
    /**
     * @brief Information about a block
     * Used as a placeholder for derived structs
     */
    struct BlockInfo {
        virtual ~BlockInfo() = default;
        virtual std::string toString() const = 0; // Pure virtual function
    };

    class Block {
    public:
        /**
         * @brief Retrieve the variant type of the block.
         * Get whether if the block is a Supplier, Transporter or Transaction block.
         *
         * @return
         */
        [[nodiscard]] blockchain::enums::BlockType getType() const;

        /**
         * @brief Get the height of the blockN
         *
         * @return
         */
        [[nodiscard]] int getHeight() const;

        /**
         * @brief Get the hash of the previous block
         *
         * @return
         */
        [[nodiscard]] int getNonce() const;

        /**
         * @brief Get the header of the block.
         * Get by reference to enable modification of the header.
         *
         * @return
         */
        [[nodiscard]] BlockHeader& getHeader();

        /**
         * @brief Get the header of the block.
         *
         * @return
         */
        [[nodiscard]] BlockHeader getHeader() const;

        /**
         * @brief Check whether if the block is a genesis block
         *
         * @return
         */
        [[nodiscard]] bool isGenesis() const;

        /**
         * @brief Check whether if the block is visible to the participant.
         *
         * @return
         */
        [[nodiscard]] bool isVisible() const;

        /**
         * @brief Set the initial block of the blockchain
         *
         * @param genesisValue
         */
        void setGenesis(bool genesisValue);

        /**
         * @brief Set the visibility of the block
         * Usually done after an operation on the block.
         *
         * @param visibility
         */
        void setVisible(bool visibility);

        /**
         * @brief Set the information string of the block
         *
         * @param information
         */
        void setInformationString(const std::string& information);

        /**
         * @brief Creates a deep copy of the current block's instance
         *
         * @return
         */
        virtual std::shared_ptr<Block> clone() const = 0;

    protected:
        /**
         * @brief The type of the block
         */
        blockchain::enums::BlockType type;

        /**
         * @brief The height of the block
         */
        int height;

        /*
         * @brief The header of the block
         */
        blockchain::BlockHeader header;

        /**
         * @brief Whether if the block is a genesis block
         */
        bool genesis = false;

        /**
         * @brief Whether if the block is visible to the participant
         */
        bool visible = true;

        /**
         * @brief The constructor for the block
         *
         * @param version
         * @param bits
         * @param height
         * @param previousHash
         * @param information
         * @param type
         * @param nonce
         * @param currentHash
         * @param visible
         */
        Block(const int version, const std::string bits, int height, const std::string& previousHash, const std::string& information, blockchain::enums::BlockType type, int nonce = 0, const std::string& currentHash = "", bool visible = true);
    };
} // namespace blockchain
