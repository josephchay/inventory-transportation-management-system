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

        static std::function<std::string(std::string)> getHashFunction(blockchain::enums::BlockType type);
        std::string mine(std::function<std::string(std::string)> hashFunction);

        BlockHeader& updateEditableData(const std::string informationString, const std::string prevHash = "");

        // setters
        void setHash(const std::string& hash);
        void setPrevHash(const std::string& prevHash);
        void setMerkleRoot(const std::string& merkleRoot);
        void setTimestamp(time_t timestamp);
        void setFormattedTimestamp(const std::string& formattedTimestamp);
        void setInformationString(const std::string& informationString);
        void setNonce(int nonce);
        void setMined(bool mined);

        // getters
        [[nodiscard]] blockchain::enums::BlockType getType() const;
        [[nodiscard]] std::string getHash() const;
        [[nodiscard]] std::string getPrevHash() const;
        [[nodiscard]] std::string getMerkleRoot() const;
        [[nodiscard]] time_t getTimestamp() const;
        [[nodiscard]] std::string getFormattedTimestamp() const;
        [[nodiscard]] std::string getInformationString() const;
        [[nodiscard]] int getNonce() const;
        [[nodiscard]] bool isMined() const;

    protected:
        blockchain::enums::BlockType type;
        int version;
        std::string bits;
        std::string hash;
        std::string previousHash;
        std::string merkleRoot;
        time_t timestamp;
        std::string formattedTimestamp;
        std::string informationString;
        int nonce;
        bool mined = false;

        std::basic_string<char> generateHash(const std::function<std::string(std::string)> &hashFunction) const;
    };
} // namespace blockchain