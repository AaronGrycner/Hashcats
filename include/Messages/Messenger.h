//
// Created by aaron on 4/16/24.
//

#ifndef HASHCATS_MESSENGER_H
#define HASHCATS_MESSENGER_H

#include <mpi/mpi.h>

#include "Messages.h"


class Messenger {
private:
    int rank{};

    MPI_Status status{};
    MPI_Request request{};

    std::string buffer;
    std::shared_ptr<Messages::Message> msg_buf;

    bool startListen();
    void reset_buffer();

public:
    Messenger();

    bool check_for_message();

    static void send_hello(int dest);
    static void send_acknowledge(int dest);
    static void send_goodbye(int dest);
    static void send_pcap(int dest, const FileData::PcapData &file);
    static void send_wordlist(int dest, const FileData::WordlistData &file);

    std::shared_ptr<Messages::Message> get_message() { return msg_buf; }
};

#endif //HASHCATS_MESSENGER_H
