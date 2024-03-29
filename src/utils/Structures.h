#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <vector>
#include <string>

namespace utils {
    class Structures {
    public:
        // Static function to find the index of an item in a vector of strings.
        // Returns the index of the item if found, -1 otherwise.

        /**
         * @brief Find the index of an item in a vector of strings
         *
         * @param vec
         * @param item
         * @return
         */
        static int findVectorIndex(const std::vector<std::string>& vec, const std::string& item);

        /**
         * @brief Split a line into tokens
         *
         * @param line
         * @return
         */
        static std::vector<std::string> splitLine(const std::string& line);
    };
}

#endif // DATAUTILS_H
