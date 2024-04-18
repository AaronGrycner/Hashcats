//
// Created by aaron on 3/5/24.
//

#ifndef DEFS_H
#define DEFS_H

#define TEST

// buffer size
const uint8_t BUFFER_SIZE{255};

// name of supplied wordlist
const std::string WORDLIST_FILE{"wordlist.txt"};

// name of supplied pcap file
const std::string PCAP_FILE{"pcap"};

// initial keys defs
const std::string SSH_INIT_KEYS_DIR{"setup/ssh/initial-keys/"},
                    SSH_INIT_KEY_PUBLIC{SSH_INIT_KEYS_DIR + "init_key.pub"},
                    SSH_INIT_KEY_PRIVATE{SSH_INIT_KEYS_DIR + "init_key"};

// final keys defs
const std::string SSH_FINAL_KEYS_DIR{"setup/ssh/final-keys/"},
                    SSH_FINAL_KEY_PUBLIC{SSH_FINAL_KEYS_DIR + "final_key.pub"},
                    SSH_FINAL_KEY_PRIVATE{SSH_FINAL_KEYS_DIR + "final_key"};

const std::string SSH_USER{"mpi"};

#endif //DEFS_H
