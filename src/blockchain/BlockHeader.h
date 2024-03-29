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
        /**
         * @brief Construct a new Block Header object
         *
         * @param type
         * @param version
         * @param bits
         * @param informationString
         * @param nonce
         * @param hash
         * @param previousHash
         */
        BlockHeader(blockchain::enums::BlockType type, const int version, const std::string bits, const std::string& informationString, int nonce = 0, const std::string& hash = "", const std::string& previousHash = "");

        /**
         * @brief Get the hash function object
         *
         * @param type
         * @return
         */
        static std::function<std::string(std::string)> getHashFunction(blockchain::enums::BlockType type);

        /**
         * @brief Mine the block
         *
         * @param hashFunction
         * @return
         */
        std::string mine(std::function<std::string(std::string)> hashFunction);

        /**
         * @brief Update the editable data
         *
         * @param informationString
         * @param prevHash
         * @return
         */
        BlockHeader& updateEditableData(const std::string informationString, const std::string& prevHash = "");

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
        blockchain::enums::BlockType type; /** The type of the block */
        int version; /** The version of the block */
        std::string bits; /** The bits which is used for mining */
        std::string hash; /** The hash of the block */
        std::string previousHash; /** The previous hash of the block */
        std::string merkleRoot; /** The merkle root which contains the information of the block */
        time_t timestamp; /** The timestamp of the block */
        std::string formattedTimestamp; /** The formatted timestamp into human-readable datetime of the block */
        std::string informationString; /** The information string of the block */
        int nonce; /** The nonce of the block */
        bool mined = false; /** Whether if the block is mined */

        /**
         * @brief Generate a new hash based on the hash function
         *
         * @param hashFunction Either uses the SHA256 or the SHA384, or SHA512 hash function
         * @return
         */
        std::basic_string<char> generateHash(const std::function<std::string(std::string)> &hashFunction) const;
    };
} // namespace blockchain