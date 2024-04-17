//
// Created by aaron on 4/16/24.
//

#ifndef HASHCATS_MESSENGER_H
#define HASHCATS_MESSENGER_H

#include <mpi/mpi.h>
#include <queue>

#include "Messages.h"


class Messenger {
private:
    int rank{};
    MPI_Status status{};
    MPI_Request request{};

    std::unique_ptr<Messages::Message> msgBuf = std::make_unique<Messages::Message>();

    void parse_MPI_Status(MPI_Status &status);
    bool startListen();

public:
    Messenger() { MPI_Comm_rank(MPI_COMM_WORLD, &rank); }

    Messages::Message* check_for_message();

};

#endif //HASHCATS_MESSENGER_H
