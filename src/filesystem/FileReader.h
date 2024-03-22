#ifndef DATA_READER_H
#define DATA_READER_H

#include <string>
#include <set>
#include <vector>
#include <regex>

namespace data {
    class FileReader {
    public:
        explicit FileReader(const std::string& filePath);

        void parseFile(const std::string& filePath);
        std::vector<std::string> getAllInitialOptions() const;
        std::vector<std::string> getDataById(const std::string& id) const;
        static std::vector<std::string> parseBracketOptions(const std::string& bracketedString);

    private:
        std::vector<std::string> orderedOptions;
        std::map<std::string, std::vector<std::string>> idToDataMap;

        static void trim(std::string& s);
        static void trimSquareBrackets(std::string& str);
        static std::vector<std::string> splitLine(const std::string& line);
        static std::set<std::string> parseOptions(const std::string& options);
    };
} // namespace data

#endif // DATA_READER_H
