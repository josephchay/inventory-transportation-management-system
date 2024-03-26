#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include <fstream>

namespace filesystem {
    class FileWriter {
    public:
        explicit FileWriter(const std::string& filePath);
        ~FileWriter();
        void writeLine(const std::string& line);
        static void modifyCell(const std::string& filePath, int rowNum, int colNum, const std::string& newValue);
        static void clearFile(const std::string& filePath);

    private:
        std::ofstream outputFile;
        static std::string modifyLine(const std::string& line, int colNum, const std::string& newValue);
    };
}

#endif // FILEWRITER_H
