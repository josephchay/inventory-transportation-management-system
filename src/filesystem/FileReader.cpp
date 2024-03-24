#include "FileReader.h"
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
            default:
                std::cerr << "Unsupported file type" << std::endl;
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

    const std::vector<BlockInfo>& FileReader::getBlocks() const {
        return blocks;
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
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::string line;
        BlockInfo currentBlock;
        bool blockStarted = false;

        while (getline(file, line)) {
            if (line.find("Block Type:") != std::string::npos) {
                if (blockStarted) {
                    // Save the previous block before starting a new one
                    blocks.push_back(currentBlock);
                    currentBlock = BlockInfo(); // Reset for next block
                }
                currentBlock.blockType = extractBlockData(line);
                blockStarted = true;
            } else if (line.find("Block Number:") != std::string::npos) {
                currentBlock.blockNumber = std::stoi(extractBlockData(line));
            } else if (line.find("Current Hash:") != std::string::npos) {
                currentBlock.currentHash = extractBlockData(line);
            } else if (line.find("Previous Hash:") != std::string::npos) {
                currentBlock.previousHash = extractBlockData(line);
            } else if (line.find("Timestamp:") != std::string::npos) {
                currentBlock.timestamp = extractBlockData(line);
            } else if (line.find("Information:") != std::string::npos) {
                currentBlock.information = extractBlockData(line);
            }
        }

        if (blockStarted) { // Don't forget to add the last block if there is one
            blocks.push_back(currentBlock);
        }
    }

    std::string FileReader::extractBlockData(const std::string& line) const {
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

    std::set<std::string> FileReader::parseOptions(const std::string& options) {
        // Apply the trimming function to remove square brackets if they exist
        std::string trimmedOptions = options;
        trimSquareBrackets(trimmedOptions);

        std::set<std::string> results;
        std::stringstream ss(trimmedOptions);
        std::string item;

        while (std::getline(ss, item, ',')) {
            // Further trimming whitespace if necessary
            trim(item);
            results.insert(item);
        }

        return results;
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

    void FileReader::trimSquareBrackets(std::string& str) {
        if (!str.empty()) {
            // Check and remove leading '[' if present
            if (str.front() == '[') {
                str.erase(str.begin());
            }
            // After removing the leading '[', check if the string is not empty
            if (!str.empty() && str.back() == ']') {
                // Check and remove trailing ']' if present
                str.pop_back();
            }
        }
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
