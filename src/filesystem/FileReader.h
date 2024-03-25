#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <set>
#include <vector>
#include <regex>
#include "../blockchain/enums/BlockType.cpp"

namespace filesystem {
    enum class DataType {
        OPTION,
        CHAIN
    };

    struct BlockInfo {
        blockchain::enums::BlockType type;
        int height;
        int nonce;
        std::string currentHash;
        std::string previousHash;
        std::string timestamp;
        std::string information;
    };

    class FileReader {
    public:
        explicit FileReader(const std::string& filePath, DataType datatype);

        void parseOptionFile(const std::string& filePath);
        void parseChainFile(const std::string& filePath);
        std::vector<std::string> getAllInitialOptions() const;
        std::vector<std::string> getDataById(const std::string& id) const;
        static std::vector<std::string> parseBracketOptions(const std::string& bracketedString);

        const std::vector<BlockInfo>& getBlocks() const;
        static std::vector<int> extractBlockIds(const std::string& filePath, const std::string& blockType);

    private:
        std::vector<BlockInfo> blocks;
        std::vector<std::string> orderedOptions;

        std::map<std::string, std::vector<std::string>> idToDataMap;
        static void trim(std::string& s);
        static void trimSquareBrackets(std::string& str);
        static std::vector<std::string> splitLine(const std::string& line);
        static std::set<std::string> parseOptions(const std::string& options);
        std::string extractBlockData(const std::string& line) const;
    };
} // namespace filesystem

#endif // FILEREADER_H
