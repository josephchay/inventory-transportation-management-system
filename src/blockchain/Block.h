#pragma once

#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "BlockHeader.h"
#include "enums/BlockType.h"

namespace blockchain {
    class Block {
    public:
        [[nodiscard]] blockchain::enums::BlockType getType() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] int getNonce() const;
        [[nodiscard]] std::string getCurrentHash() const;
        [[nodiscard]] std::string getPrevHash() const;
        [[nodiscard]] std::string getMerkleRoot() const;
        [[nodiscard]] time_t getTimestamp() const;
        [[nodiscard]] std::string getFormattedTimestamp() const;
        [[nodiscard]] std::string getInformationString() const;
        [[nodiscard]] bool isGenesis() const;

        void setGenesis(bool genesisValue);

    protected:
        blockchain::enums::BlockType type;
        int height;
        blockchain::BlockHeader header;
        bool genesis = false;

        Block(const int version, const std::string bits, int height, const std::string& previousHash, const std::string& information, blockchain::enums::BlockType type, int nonce = 0, const std::string& currentHash = "");
    };
} // namespace blockchain
