#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include <fstream>

namespace filesystem {
    class FileWriter {
    public:
        /**
         * @brief Construct a new FileWriter object
         *
         * @param filePath
         */
        explicit FileWriter(const std::string& filePath);

        /**
         * @brief Destroy the FileWriter object
         */
        ~FileWriter();

        /**
         * @brief Write a line to the file
         * The file path is determined by the constructor
         *
         * @param line
         */
        void writeLine(const std::string& line);

        /**
         * @brief Modify a cell in a text file
         * Each cell is separated by a comma
         *
         * @param filePath
         * @param rowNum
         * @param colNum
         * @param newValue
         */
        static void modifyCell(const std::string& filePath, int rowNum, int colNum, const std::string& newValue);

        /**
         * @brief Clear the contents of a file
         *
         * @param filePath
         */
        static void clearFile(const std::string& filePath);

    private:
        /**
         * @brief The output file stream
         */
        std::ofstream outputFile;
        static std::string modifyLine(const std::string& line, int colNum, const std::string& newValue);
    };
}

#endif // FILEWRITER_H
