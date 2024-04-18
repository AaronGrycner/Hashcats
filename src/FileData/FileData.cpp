#include <fstream>
#include <iostream>
#include <vector>

#include "FileData/FileData.h"
#include "Messages.h"

namespace FileData {

    FileData::FileData(const std::string &p) {
        read_file(p);
    }

    void FileData::read_file(const std::string &path) {
        std::ifstream file(path, std::ios::binary); // Open in binary mode to avoid platform-specific line ending conversions
        if (!file) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return; // Optionally handle this more robustly, e.g., by setting an error state
        }

        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // Reserve memory for the entire file content and read it in one go
        data.resize(fileSize); // Use resize to allocate exact memory needed
        if (!file.read(&data[0], static_cast<int>(fileSize))) {
            std::cerr << "Error reading file: " << path << std::endl;
            data.clear(); // Clear data if read fails
        }
    }

    FileData::FileData(std::unique_ptr<char[]> data) {
        this->data = std::string(data.get(), BUFFER_SIZE);
    }

    std::vector<WordlistData> WordlistData::split(int chunks) {
        std::vector<WordlistData> result(chunks);  // Pre-allocate vector with empty WordlistData elements
        size_t start = 0;
        size_t end;
        int index = 0;

        while (start < data.length() && index < chunks) {
            // Find the next newline character from 'start'
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

        return result;
    }
}
