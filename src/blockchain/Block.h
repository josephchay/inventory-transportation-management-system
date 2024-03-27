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
        [[nodiscard]] blockchain::enums::BlockType getType() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] int getNonce() const;
        [[nodiscard]] BlockHeader& getHeader();
        [[nodiscard]] BlockHeader getHeader() const;
        [[nodiscard]] bool isGenesis() const;
        [[nodiscard]] bool isVisible() const;

        void setGenesis(bool genesisValue);
        void setVisible(bool visibility);
        void setInformationString(const std::string& information);

        virtual std::shared_ptr<Block> clone() const = 0;

    protected:
        blockchain::enums::BlockType type;
        int height;
        blockchain::BlockHeader header;
        bool genesis = false;
        bool visible = true;

        Block(const int version, const std::string bits, int height, const std::string& previousHash, const std::string& information, blockchain::enums::BlockType type, int nonce = 0, const std::string& currentHash = "", bool visible = true);
    };
} // namespace blockchain
