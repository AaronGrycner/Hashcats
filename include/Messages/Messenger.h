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

    std::shared_ptr<Messages::Message> msg_buf= std::make_shared<Messages::Message>();

public:
    Messenger();

    bool check_for_message();
    std::shared_ptr<Messages::Message> get_message();

    static void send_hello(int dest);
    static void send_acknowledge(int dest);
    static void send_goodbye(int dest);
    static void send_pcap(int dest, const FileData::PcapData &file);
    static void send_wordlist(int dest, const FileData::WordlistData &file);

};

#endif //HASHCATS_MESSENGER_H
