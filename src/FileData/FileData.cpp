#include <fstream>
#include <iostream>
#include <vector>

#include "Logger.h"  // Make sure this includes the definition of Logger class
#include "FileData/FileData.h"

namespace FileData {

    void FileData::read_file(const std::string &path) {
        Logger::log("Attempting to read file: " + path);
        std::ifstream file(path, std::ios::binary); // Open in binary mode to avoid platform-specific line ending conversions
        if (!file) {
            Logger::log("Failed to open file: " + path);
            return; // Optionally handle this more robustly, e.g., by setting an error state
        }

        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // Reserve memory for the entire file content and read it in one go
        data.resize(fileSize); // Use resize to allocate exact memory needed
        if (!file.read(&data[0], static_cast<int>(fileSize))) {
            Logger::log("Error reading file: " + path);
            data.clear(); // Clear data if read fails
        } else {
            Logger::log("File read successfully: " + path);
        }
    }

    std::vector<WordlistData> WordlistData::split(int chunks) const {
        Logger::log("Splitting data into " + std::to_string(chunks) + " chunks.");
        std::vector<WordlistData> result(chunks);  // Pre-allocate vector with empty WordlistData elements
        size_t start = 0;
        size_t end;
        int index = 0;

        while (start < data.length() && index < chunks) {
            end = data.find('\n', start);
            if (end == std::string::npos) {
                end = data.length();  // If no newline found, use the end of the string
            }

            // Add the line to the current chunk
            result[index % chunks].data.append(data.substr(start, end - start + 1));

            // Move start to the next character after the newline
            start = end + 1;

            // Move to the next chunk index after completing one cycle
            if (++index % chunks == 0) {
                index = 0;
            }
        }

        Logger::log("Data split successfully.");
        return result;
    }
}
