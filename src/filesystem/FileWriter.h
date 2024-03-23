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

    private:
        std::ofstream outputFile;
    };
}

#endif // FILEWRITER_H
