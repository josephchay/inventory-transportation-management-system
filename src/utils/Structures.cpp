#include <sstream>
#include "Structures.h"

namespace utils {
    /**
     * @brief Static function to find the index of an item in a vector of strings
     *
     * @param vec The vector of strings
     * @param item The item to find
     * @return The index of the item if found, -1 otherwise
     */
    int Structures::findVectorIndex(const std::vector<std::string>& vec, const std::string& item) {
        for (size_t i = 0; i < vec.size(); ++i) {
            if (vec[i] == item) {
                return static_cast<int>(i); // Item found, return index
            }
        }
        return -1; // Item not found, return -1
    }

    std::vector<std::string> Structures::splitLine(const std::string& line) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        return tokens;
    }
}
