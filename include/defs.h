//
// Created by aaron on 3/5/24.
//

#ifndef DEFS_H
#define DEFS_H

#define TEST

// name of supplied wordlist
const std::string WORDLIST_FILE{"wordlists/wordlist.txt"};

// name of supplied pcap file
const std::string HCCAPX_FILE{"hccapxs/nokia.hc22000"};

// success file
const std::string SUCCESS_FILE{"/home/aaron/success.txt"};

// hashcat command
const std::string HASHCAT_COMMAND{"hashcat -m 22000 -o " + SUCCESS_FILE + " " + HCCAPX_FILE + " " + WORDLIST_FILE};

// hashcat potfile
const std::string HASHCAT_POTFILE{"/home/aaron/.local/share/hashcat/hashcat.potfile"}, DELETE_POTFILE{"rm " + HASHCAT_POTFILE};

#endif //DEFS_H
