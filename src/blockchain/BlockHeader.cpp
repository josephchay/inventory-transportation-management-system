#include "BlockHeader.h"
#include "../../libs/sha256/sha256.h"
#include "../utils/Datetime.h"
#include <random>
#include <algorithm>
#include <iostream>

namespace blockchain {
    std::vector<uint8_t> hexStringToBytes(const std::string& hex) {
        std::vector<uint8_t> bytes;

        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16));
            bytes.push_back(byte);
        }

        return bytes;
    }

    // Helper methods to append data to the block header vector for hashing
    void appendIntToVector(std::vector<uint8_t>& vec, uint32_t value) {
        for (int i = 0; i < 4; ++i) {
            vec.push_back((value >> (i * 8)) & 0xFF);
        }
    }

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

    BlockHeader::BlockHeader(const int version, const std::string bits, const std::string& informationString, int nonce, const std::string& currentHash, const std::string& previousHash)
            : version(version), bits(bits), informationString(informationString) {
        // Initialize timestamp with the current date and time
        std::time_t currentTime = std::time(nullptr);
        this->timestamp = currentTime;
        this->formattedTimestamp = utils::Datetime::formatTimestamp(currentTime);

        // For a genesis block, set the previous block hash to initially 64 zeros
        this->previousHash = previousHash.empty() || previousHash == "0" ? std::string(64, '0') : previousHash;
        this->merkleRoot = sha256(informationString);

        if (currentHash.empty()) {
            this->hash = mine();
        } else {
            this->hash = currentHash;
            this->nonce = nonce;
        }

        // Set the previous hash to the mined hash for genesis block.
        if (previousHash.empty() || previousHash == "0") {
            this->previousHash = this->hash;
        }
    }

    std::string BlockHeader::mine() {
        // Target defined for a hash to start with "0000", so first 2 bytes should be zero
        std::vector<uint8_t> targetPrefix = {0x00, 0x00};

        // The current hash is in hexadecimal
        std::string currentHashHex;

        // Begin mining process
        this->nonce = 0;
        bool hashFound = false;

        do {
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
            // Hash the block header using SHA256
            currentHashHex = sha256(blockHeaderStr);

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
            return currentHashHex;
        } else {
            std::cout << std::endl << std::endl << "Mining ended, nonce limit reached." << std::endl << std::endl;
            return "";
        }
    }

    // Getter methods
    std::string BlockHeader::getHash() const { return hash; }
    std::string BlockHeader::getPrevHash() const { return previousHash; }
    std::string BlockHeader::getMerkleRoot() const { return merkleRoot; }
    time_t BlockHeader::getTimestamp() const { return timestamp; }
    std::string BlockHeader::getFormattedTimestamp() const { return formattedTimestamp; }
    std::string BlockHeader::getBits() const { return bits; }
    std::string BlockHeader::getInformationString() const { return informationString; }
    int BlockHeader::getNonce() const { return nonce; }
} // namespace blockchain