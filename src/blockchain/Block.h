#pragma once

#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "BlockHeader.h"

namespace blockchain {
    class Block {
    public:
        [[nodiscard]] std::string getType() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] int getNonce() const;
        [[nodiscard]] std::string getCurrentHash() const;
        [[nodiscard]] std::string getPrevHash() const;
        [[nodiscard]] time_t getTimestamp() const;
        [[nodiscard]] std::string getFormattedTimestamp() const;
        [[nodiscard]] std::string getInformationString() const;
        [[nodiscard]] bool isGenesis() const;

        void setGenesis(bool genesisValue);

    protected:
        std::string blockType;
        int height;
        blockchain::BlockHeader header;
        bool genesis = false;

        Block(int height, const std::string& previousHash, const std::string& information, const std::string& blockType, int nonce = 0, const std::string& currentHash = "");
    };
} // namespace blockchain
