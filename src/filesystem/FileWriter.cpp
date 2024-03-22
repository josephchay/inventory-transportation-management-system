#include "FileWriter.h"
#include <iostream>

namespace filesystem {
    // Constructor that opens the file
    FileWriter::FileWriter(const std::string& filePath) {
        outputFile.open(filePath, std::ios::out | std::ios::app); // Open in append mode
        if (!outputFile.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
        }
    }

    // Destructor that closes the file
    FileWriter::~FileWriter() {
        if (outputFile.is_open()) {
            outputFile.close();
        }
    }

    // Method to write a single line to the file
    void FileWriter::writeLine(const std::string& line) {
        if (outputFile.is_open()) {
            outputFile << line << std::endl;
        } else {
            std::cerr << "Attempted to write to an unopened file." << std::endl;
        }
    }
}
