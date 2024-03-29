#include "BlockHeader.h"
#include "../utils/Datetime.h"
#include "../../libs/sha256/sha256.h"
#include "../../libs/sha384/sha384.h"
#include "../../libs/sha512/sha512.h"
#include <random>
#include <algorithm>
#include <iostream>

namespace blockchain {
    /**
     * @brief Convert a hexadecimal string to a byte array
     * Helper method
     *
     * @param hex
     * @return
     */
    std::vector<uint8_t> hexStringToBytes(const std::string& hex) {
        std::vector<uint8_t> bytes;

        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16));
            bytes.push_back(byte);
        }

        return bytes;
    }

    /**
     * @brief Append data to the block header vector for hashing
     * Helper method
     *
     * @param vec
     * @param value
     */
    void appendIntToVector(std::vector<uint8_t>& vec, uint32_t value) {
        for (int i = 0; i < 4; ++i) {
            vec.push_back((value >> (i * 8)) & 0xFF);
        }
    }

    /**
     * @brief Append hexadecimal data to the block header vector for hashing
     * Helper method
     *
     * @param vec
     * @param hex
     */
    void appendHexToVector(std::vector<uint8_t>& vec, const std::string& hex) {
        // Ensure the hex string's length is even
        if (hex.length() % 2 != 0) {
            throw std::runtime_error("Invalid hexadecimal string.");
        }

        // Convert each pair of hexadecimal characters to a byte and append to the vector
        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            char byte = static_cast<char>(std::stoul(byteString, nullptr, 16));
            vec.push_back(static_cast<uint8_t>(byte));
        }
    }

    std::function<std::string(std::string)> BlockHeader::getHashFunction(blockchain::enums::BlockType type) {
        switch (type) {
            case blockchain::enums::BlockType::SUPPLIER:
            default: // Default to SHA-256
                return sha256;
            case blockchain::enums::BlockType::TRANSPORTER:
                return sha384;
            case blockchain::enums::BlockType::TRANSACTION:
                return sha512;
        }
    }

    BlockHeader::BlockHeader(blockchain::enums::BlockType type, const int version, const std::string bits, const std::string& informationString, int nonce, const std::string& currentHash, const std::string& previousHash)
            : type(type), version(version), bits(bits), informationString(informationString) {
        // Initialize timestamp with the current date and time
        setTimestamp(std::time(nullptr)); // Current time

        // For a genesis block, set the previous block hash to initially 64 zeros
        setPrevHash(previousHash.empty() || previousHash == "0" ? std::string(64, '0') : previousHash);
        setMerkleRoot(getHashFunction(type)(informationString));

        if (currentHash.empty()) {
            setHash(mine(getHashFunction(type)));
        } else {
            setMined(true); // Block is already mined (from file data
            setHash(currentHash);
            setNonce(nonce);
        }

        // Set the previous hash to the mined hash for genesis block.
        if (previousHash.empty() || previousHash == "0") {
            setPrevHash(this->hash);
        }
    }

    std::string BlockHeader::mine(std::function<std::string(std::string)> hashFunction) {
        // Target defined for a hash to start with "0000", so first 2 bytes should be zero
        std::vector<uint8_t> targetPrefix = {0x00, 0x00};

        // The current hash is in hexadecimal
        std::string currentHashHex;

        // Begin mining process
        this->nonce = 0;
        bool hashFound = false;

        do {
            currentHashHex = generateHash(hashFunction);

            // Convert the current hash back to bytes for comparison
            std::vector<uint8_t> currentHashBytes = hexStringToBytes(currentHashHex);

            // Check if the first two bytes of the hash are zeros (i.e., check for "0000" prefix)
            hashFound = std::equal(targetPrefix.begin(), targetPrefix.end(), currentHashBytes.begin());

            // If a valid hash is found or if we've reached the maximum nonce value, we stop
            if (hashFound || nonce == std::numeric_limits<int>::max()) {
                break;
            }

            // Increment the nonce for the next attempt
            ++this->nonce;
            std::cout << "Mining... Nonce: " << this->nonce << ", Hash: " << currentHashHex << "\r" << std::flush;
        } while (!hashFound);

        if (hashFound) {
            std::cout << std::endl << std::endl << "Block mined! Nonce: " << this->nonce << ", Hash: " << currentHashHex << std::endl << std::endl;
            setMined(true);
            return currentHashHex;
        } else {
            std::cout << std::endl << std::endl << "Mining ended, nonce limit reached." << std::endl << std::endl;
            return "";
        }
    }

    std::basic_string<char> BlockHeader::generateHash(const std::function<std::string(std::string)> &hashFunction) const {
        // Construct the block header as a byte array for hashing
        std::vector<uint8_t> blockHeader;

        appendIntToVector(blockHeader, version);
        appendHexToVector(blockHeader, previousHash);
        appendHexToVector(blockHeader, merkleRoot); // in hex value
        // Timestamp needs to be converted to bytes and appended
        appendIntToVector(blockHeader, static_cast<uint32_t>(timestamp));
        appendHexToVector(blockHeader, bits);
        appendIntToVector(blockHeader, nonce);

        // Convert blockHeader to a string for SHA256 hashing
        std::string blockHeaderStr(blockHeader.begin(), blockHeader.end());

        // Hash the block header using the provided hash function
        return hashFunction(blockHeaderStr);
    }

    BlockHeader& BlockHeader::updateEditableData(const std::string informationString, const std::string& prevHash) {
        setInformationString(informationString);
        setMerkleRoot(getHashFunction(type)(informationString));
        setPrevHash(prevHash.empty() || prevHash == "0" ? std::string(64, '0') : prevHash);
        setHash(generateHash(getHashFunction(type)));
        setMined(false); // Reset mined status after updating data, currentParticipant has the choice to mine again
        setPrevHash(prevHash.empty() || prevHash == "0" ? hash : prevHash);

        return *this;
    }

    // Getter methods
    blockchain::enums::BlockType BlockHeader::getType() const { return type; }
    std::string BlockHeader::getHash() const { return hash; }
    std::string BlockHeader::getPrevHash() const { return previousHash; }
    std::string BlockHeader::getMerkleRoot() const { return merkleRoot; }
    time_t BlockHeader::getTimestamp() const { return timestamp; }
    std::string BlockHeader::getFormattedTimestamp() const { return formattedTimestamp; }
    std::string BlockHeader::getInformationString() const { return informationString; }
    int BlockHeader::getNonce() const { return nonce; }
    bool BlockHeader::isMined() const { return mined; }

    // Setter methods
    void BlockHeader::setHash(const std::string& hash) { this->hash = hash; }
    void BlockHeader::setPrevHash(const std::string& prevHash) { this->previousHash = prevHash; }
    void BlockHeader::setMerkleRoot(const std::string& merkleRoot) { this->merkleRoot = merkleRoot; }
    void BlockHeader::setTimestamp(time_t timestamp) {
        this->timestamp = timestamp;
        this->formattedTimestamp = utils::Datetime::formatTimestamp(timestamp);
    }
    void BlockHeader::setFormattedTimestamp(const std::string& formattedTimestamp) { this->formattedTimestamp = formattedTimestamp; }
    void BlockHeader::setInformationString(const std::string& informationString) { this->informationString = informationString; }
    void BlockHeader::setNonce(int nonce) { this->nonce = nonce; }
    void BlockHeader::setMined(bool mined) { this->mined = mined; }
} // namespace blockchain