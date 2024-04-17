//
// Created by aaron on 4/16/24.
//

#include "Messenger.h"
#include "Logger.h"

using namespace Messages;


void Messenger::parse_MPI_Status(MPI_Status &status) {
    int count{};

    msgBuf->set_source(status.MPI_SOURCE);
    msgBuf->set_dest(status.MPI_TAG);

    MPI_Get_count(&status, MPI_CHAR, &count);
    msgBuf->set_count(count);
}

Message* Messenger::check_for_message() {
    int flag, ret{MPI_Test(&request, &flag, &status)};

    Message* msg{nullptr};

    if ((ret == MPI_SUCCESS) && flag) {
        parse_MPI_Status(status);

        Logger::log(std::to_string(rank) + " successfully received message from " + std::to_string(msgBuf->source()));

        startListen(); // restart async listen on successful message receive

        msg = msgBuf.release();
        msgBuf = std::make_unique<Message>();

        return msg;

    } else if ((ret == MPI_SUCCESS) && !flag) {
        Logger::log(std::to_string(rank) + " succesfully checked messages but none found");
        return nullptr;
    } else {
        Logger::log(std::to_string(rank) + " message check fail");
        return nullptr;
    }
}

bool Messenger::startListen() {
    int ret{MPI_Irecv(msgBuf->buf(), BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request) ==
            MPI_SUCCESS};

    if (ret) {
        Logger::log(std::to_string(rank) + " successfully started async receive.");
    } else {
        Logger::log(std::to_string(rank) + std::to_string(rank) + " failed to start async receive");
    }

    return ret;
}