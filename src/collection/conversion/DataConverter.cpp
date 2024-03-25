#include "DataConverter.h"
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

namespace conversion {
    // Utility function to trim whitespace from start and end of a string
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // Splits a string into a vector of strings at each instance of a delimiter
    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(trim(token));
        }
        return tokens;
    }

    // Parses a block of text into a map of key-value pairs
    std::map<std::string, std::string> parseBlockInfo(const std::string& blockInfo) {
        std::map<std::string, std::string> infoMap;
        auto lines = split(blockInfo, '\n');
        for (const auto& line : lines) {
            auto keyValue = split(line, ':');
            if (keyValue.size() == 2) {
                infoMap[trim(keyValue[0])] = trim(keyValue[1]);
            }
        }
        return infoMap;
    }

    // Parses the "Information" field into a map of key-value pairs
    std::map<std::string, std::string> parseInformationField(const std::string& infoField) {
        std::map<std::string, std::string> infoMap;
        auto infoPairs = split(infoField, '|');
        for (const auto& pair : infoPairs) {
            auto keyValue = split(pair, ':');
            if (keyValue.size() == 2) {
                infoMap[trim(keyValue[0])] = trim(keyValue[1]);
            }
        }
        return infoMap;
    }

    blockchain::SupplierBlock DataConverter::convertToSupplierBlock(int version, const std::string bits, int height, int nonce, const std::string& currentHash, const std::string& previousHash, const std::string& data) {
        auto infoDetails = parseInformationField(data);
        blockchain::SupplierInfo info(std::stoi(infoDetails["ID"]), infoDetails["Name"], infoDetails["Location"], infoDetails["Branch"]);

        return blockchain::SupplierBlock(version, bits, height, previousHash, info, nonce, currentHash);
    }

    blockchain::TransporterBlock DataConverter::convertToTransporterBlock(int version, const std::string bits, int height, int nonce, const std::string& currentHash, const std::string& previousHash, const std::string& data) {
        auto infoDetails = parseInformationField(data);
        blockchain::TransporterInfo info(std::stoi(infoDetails["ID"]), infoDetails["Name"], infoDetails["Product Type"], infoDetails["Transportation Type"], infoDetails["Ordering Type"], std::stod(infoDetails["Ordering Amount (Kg)"]));

        return blockchain::TransporterBlock(version, bits, height, previousHash, info, nonce, currentHash);
    }

    blockchain::TransactionBlock DataConverter::convertToTransactionBlock(int version, const std::string bits, int height, int nonce, const std::string& currentHash, const std::string& previousHash, const std::string& data) {
        auto infoDetails = parseInformationField(data);

        blockchain::TransactionInfo info(std::stoi(infoDetails["ID"]), infoDetails["Retailer Per-Trip Credit Balance"], infoDetails["Annual Ordering Credit Balance"], infoDetails["Payment Type"], infoDetails["Product Ordering Limit"]);
        return blockchain::TransactionBlock(version, bits, height, previousHash, info, nonce, currentHash);
    }
}
