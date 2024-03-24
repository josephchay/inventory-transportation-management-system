#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <vector>
#include <string>

namespace utils {
    class Structures {
    public:
        // Static function to find the index of an item in a vector of strings.
        // Returns the index of the item if found, -1 otherwise.
        static int findVectorIndex(const std::vector<std::string>& vec, const std::string& item);
    };
}

#endif // DATAUTILS_H
