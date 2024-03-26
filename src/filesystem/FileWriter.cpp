#include "FileWriter.h"
#include <iostream>
#include <vector>

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

    void FileWriter::modifyCell(const std::string& filePath, int rowNum, int colNum, const std::string& newValue) {
        std::ifstream inputFile(filePath);
        std::vector<std::string> lines;
        std::string line;
        int currentRow = 0;

        if (!inputFile.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }

        while (std::getline(inputFile, line)) {
            if (currentRow == rowNum) {
                std::string modifiedLine = modifyLine(line, colNum, newValue);
                lines.push_back(modifiedLine);
            } else {
                lines.push_back(line);
            }
            ++currentRow;
        }

        inputFile.close();

        // Now, write the modified lines back to the file
        std::ofstream outputFile(filePath);
        if (!outputFile.is_open()) {
            std::cerr << "Failed to open file for writing: " << filePath << std::endl;
            return;
        }

        for (const auto& modifiedLine : lines) {
            outputFile << modifiedLine << std::endl;
        }
    }

    std::string FileWriter::modifyLine(const std::string& line, int colNum, const std::string& newValue) {
        std::vector<std::string> columns;
        std::string temp;
        bool inParentheses = false;
        int currentCol = 0;
        bool replaced = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char ch = line[i];
            if (ch == '(') {
                inParentheses = true;
                temp += ch;
            } else if (ch == ')' && inParentheses) {
                temp += ch;
                inParentheses = false;
                // Check if this is the column to replace
                if (currentCol == colNum && !replaced) {
                    temp = "(" + newValue + ")";
                    replaced = true; // Ensure we don't replace more than once
                }
            } else if (ch == ',' && !inParentheses) {
                if (currentCol == colNum && !replaced) {
                    columns.push_back(newValue);
                    replaced = true;
                } else {
                    columns.push_back(temp);
                }
                temp.clear();
                currentCol++;
                continue; // Skip the rest of the loop to avoid adding the comma to temp
            } else {
                temp += ch;
            }
        }

        // Handle the last column or the only column case
        if (!temp.empty() || currentCol == colNum) {
            if (currentCol == colNum && !replaced) {
                columns.push_back(newValue);
            } else {
                columns.push_back(temp);
            }
        }

        // Reconstruct the modified line
        std::string modifiedLine;
        for (size_t i = 0; i < columns.size(); i++) {
            if (i > 0) modifiedLine += ",";
            modifiedLine += columns[i];
        }

        return modifiedLine;
    }

    void FileWriter::clearFile(const std::string& filePath) {
        // Open the file with ios::out and ios::trunc flags to clear its contents
        std::ofstream file(filePath, std::ios::out | std::ios::trunc);

        if (!file.is_open()) {
            std::cerr << "Failed to open file for clearing: " << filePath << std::endl;
        } else {
            file.close(); // Close the file after clearing its contents
        }
    }
}
