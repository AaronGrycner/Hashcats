//
// Created by aaron on 4/16/24.
//

#include "File/File.h"

#include <fstream>

namespace Files {

    File::File(std::string path) : path (std::move(path)) {
        read_file();
    }

    void File::read_file() {
        std::ifstream file(path);

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                data += line + '\n';
            }
            file.close();
        }
    }

    char* File::get_serialized() {
        return const_cast<char *>(data.c_str());
    }
}