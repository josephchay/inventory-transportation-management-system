#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>

namespace data {
    FileReader::FileReader(const std::string& filePath) {
        parseFile(filePath);
    }

    /**
     * @brief Get all IDs in the order they were read
     *
     * @return std::vector<std::string> Ids in the order they were read
     */
    std::vector<std::string> FileReader::getAllIds() const {
        return orderedIds;
    }

    std::vector<std::string> FileReader::getDataById(const std::string& id) const {
        auto it = idToDataMap.find(id);
        if (it != idToDataMap.end()) {
            return it->second;
        }
        return {}; // Return empty vector if ID not found
    }

    void FileReader::parseFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens = splitLine(line);
            if (tokens.size() >= 2) {
                std::string id = tokens[1]; // Assuming ID is the second element
                orderedIds.push_back(id);
                idToDataMap[id] = tokens;
            }
        }
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
            } else if (ch == '(') {
                inParentheses = true; // Set flag when entering parentheses
                // Do not add '(' to token
                continue; // Skip the current iteration to avoid adding '(' to the token
            } else if (ch == ')' && inParentheses) {
                inParentheses = false; // Reset flag when leaving parentheses
                // Do not add ')' to token, and continue to prevent breaking the token here
                continue; // Skip the current iteration to avoid adding ')' to the token
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
} // namespace data
