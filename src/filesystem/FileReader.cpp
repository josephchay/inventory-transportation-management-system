#include "FileReader.h"
#include "../blockchain/enums/BlockAttribute.h"
#include "../utils/Structures.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

namespace filesystem {
    FileReader::FileReader(const std::string& filePath, DataType datatype) {
        switch (datatype) {
            case DataType::OPTION:
                parseOptionFile(filePath);
                break;
            case DataType::CHAIN:
                parseChainFile(filePath);
                break;
            case DataType::PARTICIPANTS:
                parseParticipantFile(filePath);
                break;
            default:
                std::cerr << "Unsupported file type" << std::endl;
                break;
        }
    }

    /**
     * @brief Get all IDs in the order they were read
     *
     * @return std::vector<std::string> Ids in the order they were read
     */
    std::vector<std::string> FileReader::getAllInitialOptions() const {
        return orderedOptions;
    }

    const std::vector<BlockData>& FileReader::getBlocks() const {
        return blocks;
    }

    const std::vector<authentication::Participant>& FileReader::getParticipants() const {
        return participants;
    }

    std::vector<std::string> FileReader::getDataById(const std::string& id) const {
        auto it = idToDataMap.find(id);
        if (it != idToDataMap.end()) {
            return it->second;
        }
        return {}; // Return empty vector if ID not found
    }

    void FileReader::parseOptionFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens = splitLine(line);
            if (tokens.size() >= 2) {
                std::string id = tokens[1]; // Assuming ID is the second element
                orderedOptions.push_back(id);
                idToDataMap[id] = tokens;
            }
        }
    }

    std::vector<int> FileReader::extractBlockIds(const std::string& filePath, const std::string& blockType) {
        std::ifstream file(filePath);
        std::vector<int> ids;
        std::string line;
        bool isTargetBlock = false;

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return ids;
        }

        while (std::getline(file, line)) {
            // Identify the start of the target block
            if (line.find("Block Type: " + blockType) != std::string::npos) {
                isTargetBlock = true;
            }

            // Once inside the target block, look for the "Information" line
            if (isTargetBlock && line.find("Information: ") != std::string::npos) {
                // Extract ID from the Information line
                std::istringstream iss(line);
                std::string part;
                while (std::getline(iss, part, '|')) {
                    std::size_t idPos = part.find("ID: ");
                    if (idPos != std::string::npos) {
                        try {
                            std::string idStr = part.substr(idPos + 4); // 4 is the length of "ID: "
                            int id = std::stoi(idStr);
                            ids.push_back(id);
                            break; // Assuming only one ID per Information line
                        } catch (const std::exception& e) {
                            std::cerr << "Error converting ID to integer: " << e.what() << std::endl;
                        }
                    }
                }
                isTargetBlock = false; // Reset for the next block
            }
        }

        return ids;
    }

    void FileReader::parseChainFile(const std::string& filePath) {
        using namespace blockchain::enums;

        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::string line;
        BlockData currentBlock;
        bool blockStarted = false;

        while (getline(file, line)) {
            if (line.find(BlockAttributeUtils::toString(BlockAttribute::TYPE) + ":") != std::string::npos) {
                if (blockStarted) {
                    // Save the previous block before starting a new one
                    blocks.push_back(currentBlock);
                    currentBlock = BlockData(); // Reset for next block
                }
                currentBlock.type = BlockTypeUtils::fromString(extractBlockData(line));
                blockStarted = true;
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::HEIGHT)+ ":") != std::string::npos) {
                currentBlock.height = std::stoi(extractBlockData(line));
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::NONCE) + ":") != std::string::npos) {
                currentBlock.nonce = std::stoi(extractBlockData(line));
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::HASH) + ":") != std::string::npos) {
                currentBlock.currentHash = extractBlockData(line);
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::PREV_HASH) + ":") != std::string::npos) {
                currentBlock.previousHash = extractBlockData(line);
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::TIMESTAMP) + ":") != std::string::npos) {
                currentBlock.timestamp = extractBlockData(line);
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::INFORMATION) + ":") != std::string::npos) {
                currentBlock.information = extractBlockData(line);
            } else if (line.find(BlockAttributeUtils::toString(BlockAttribute::VISIBLE) + ":") != std::string::npos) {
                currentBlock.visible = extractBlockData(line) == "true";
            }
        }

        if (blockStarted) { // Add the last block if there is one
            blocks.push_back(currentBlock);
        }
    }

    void FileReader::parseParticipantFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        while (getline(file, line)) {
            std::vector<std::string> tokens = utils::Structures::splitLine(line);

            try {
                int id = std::stoi(tokens[0]);
                std::string username = tokens[1];
                std::string password = tokens[2];
                std::string fullName = tokens[3];
                std::string industryRole = tokens[4];
                std::string role = tokens[5];

                participants.emplace_back(id, username, password, fullName, industryRole, role);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << e.what() << std::endl;
            }
        }
    }

    std::string FileReader::extractBlockData(const std::string& line) {
        auto pos = line.find(':');
        if (pos != std::string::npos && pos + 1 < line.length()) {
            return line.substr(pos + 2); // Skip the colon and space
        }
        return "";
    }

    void FileReader::trim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    std::vector<std::string> FileReader::splitLine(const std::string& line) {
        std::vector<std::string> tokens;
        std::string token;
        bool inBrackets = false;
        bool inParentheses = false; // Flag for tracking presence inside parentheses

        for (char ch : line) {
            if (ch == '[') {
                inBrackets = true;
            } else if (ch == ']') {
                inBrackets = false;
            } else if (ch == '(' && !inBrackets) { // Only recognize '(' as special if not in brackets
                inParentheses = true;
                continue; // Skip adding '(' to token
            } else if (ch == ')' && inParentheses && !inBrackets) { // Ensure we're in parentheses but not in brackets
                inParentheses = false;
                continue; // Skip adding ')' to token
            }

            if (ch == ',' && !inBrackets && !inParentheses) {
                trim(token); // Trim whitespace before pushing
                tokens.push_back(token);
                token.clear();
            } else {
                token.push_back(ch);
            }
        }
        if (!token.empty()) {
            trim(token); // Ensure last token is trimmed and added
            tokens.push_back(token);
        }

        return tokens;
    }

    std::vector<std::string> FileReader::parseBracketOptions(const std::string& bracketedString) {
        std::vector<std::string> options;
        if (!bracketedString.empty() && bracketedString.front() == '[' && bracketedString.back() == ']') {
            std::string withoutBrackets = bracketedString.substr(1, bracketedString.size() - 2);
            std::stringstream ss(withoutBrackets);
            std::string item;
            while (std::getline(ss, item, ',')) {
                // Trim spaces if necessary
                item.erase(item.find_last_not_of(" \n\r\t") + 1);
                item.erase(0, item.find_first_not_of(" \n\r\t"));
                options.push_back(item);
            }
        }
        return options;
    }
} // namespace filesystem
