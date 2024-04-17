#include <fstream>
#include <iostream>

#include "File/File.h"

namespace Files {

    File::File(std::string p) : path(std::move(p)) {
        read_file();
    }

    const char* File::get_serialized() const {
        return data.c_str();
    }

    void File::read_file() {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return; // Optionally handle this more robustly
        }

        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // Reserve memory for the entire file content
        data.reserve(fileSize);

        std::string line;
        while (std::getline(file, line)) {
            data += line + '\n';
        }
    }

    size_t File::get_serialized_size() const {
        return data.size();
    }
}
