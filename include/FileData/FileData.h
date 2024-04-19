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
        FileData()=default;
        explicit FileData(const std::string &p);

        ~FileData() = default;

        void read_file(const std::string &path);

        size_t size() const { return data.size(); }

        [[nodiscard]] std::string get_data() const { return data; }

    };

    // Class for pcap files
    class PcapData : public FileData {
    public:
        PcapData()=default;
        explicit PcapData(const std::string& path) : FileData(path) {}

    };

    // Class for wordlist files
    class WordlistData : public FileData {
    public:
        WordlistData()=default;
        explicit WordlistData(const std::string& path) : FileData(path) {}

        std::vector<WordlistData> split(int chunks);
    };

}

#endif //HASHCATS_FILEDATA_H
