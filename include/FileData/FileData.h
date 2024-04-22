//
// Created by aaron on 4/16/24.
//

#ifndef HASHCATS_FILEDATA_H
#define HASHCATS_FILEDATA_H

#include "defs.h"

#include <string>
#include <memory>
#include <vector>

// Namespace for all file types
namespace FileData {

    // Base class for all file types
    class FileData {
    protected:
        std::string data;

    public:
        FileData() = default;
        ~FileData() = default;

        void read_file(const std::string &path);

        [[nodiscard]] size_t size() const { return data.size(); }

        void set_data(std::string d) { this->data = std::move(d); }

        [[nodiscard]] std::string get_data() const { return data; }

        void write_file(const std::string &path) const;

    };

    // Class for pcap files
    class HccapxData : public FileData {
    public:
        HccapxData()=default;

    };

    // Class for wordlist files
    class WordlistData : public FileData {
    public:
        WordlistData()=default;

        [[nodiscard]] std::vector<WordlistData> split(int chunks) const;
    };

}

#endif //HASHCATS_FILEDATA_H
