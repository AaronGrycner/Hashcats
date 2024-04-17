//
// Created by aaron on 4/16/24.
//

#ifndef HASHCATS_FILE_H
#define HASHCATS_FILE_H

#include <string>

// Namespace for all file types
namespace Files {

    // Base class for all file types
    class File {
    private:
        std::string path;
        std::string data;

        void read_file();

    public:
        explicit File(std::string path);

        ~File() = default;

        [[nodiscard]] const char *get_serialized() const;
        [[nodiscard]] size_t get_serialized_size() const;

    };

    // Class for pcap files
    class PcapFile : public File {
    private:

    public:

    };

    // Class for wordlist files
    class WordlistFile : public File {
    private:

    public:

    };

}

#endif //HASHCATS_FILE_H
