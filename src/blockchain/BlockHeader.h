#pragma once

#include <string>
#include <ctime>
#include <cstdint>
#include <vector>
#include <functional>
#include "enums/BlockType.h"

namespace blockchain {
    class BlockHeader {
    public:
        BlockHeader(blockchain::enums::BlockType type, const int version, const std::string bits, const std::string& informationString, int nonce = 0, const std::string& hash = "", const std::string& previousHash = "");

        // setters
        void setHash(const std::string& hash);
        void setPrevHash(const std::string& prevHash);
        void setMerkleRoot(const std::string& merkleRoot);
        void setTimestamp(time_t timestamp);
        void setFormattedTimestamp(const std::string& formattedTimestamp);
        void setNonce(int nonce);

        // getters
        [[nodiscard]] int getVersion() const;
        [[nodiscard]] std::string getBits() const;
        [[nodiscard]] std::string getHash() const;
        [[nodiscard]] std::string getPrevHash() const;
        [[nodiscard]] std::string getMerkleRoot() const;
        [[nodiscard]] time_t getTimestamp() const;
        [[nodiscard]] std::string getFormattedTimestamp() const;
        [[nodiscard]] std::string getInformationString() const;
        [[nodiscard]] int getNonce() const;

    protected:
        int version;
        std::string bits;
        std::string hash;
        std::string previousHash;
        std::string merkleRoot;
        time_t timestamp;
        std::string formattedTimestamp;
        std::string informationString;
        int nonce;

        std::string mine(std::function<std::string(std::string)>);
    };
} // namespace blockchain