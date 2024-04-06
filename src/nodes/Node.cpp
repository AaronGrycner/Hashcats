#include "Node.h"

#include "Log/Logger.h"
#include "Message.h"
#include "utils.h"
#include "Work.h"

Node::Node() {
    // get mpi rank and world sizes
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (startListen()) {
        Logger::log("Node rank: " + std::to_string(rank) + " successfully started Irecv.");
    }

    else {
        Logger::log("Node rank: " + std::to_string(rank) + " failed starting Irecv.");
    }
}

Node::~Node()=default;

bool Node::startListen() {
    int ret{MPI_Irecv(msgBuf.buf(), sizeof(msgBuf.buf()), MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request) == MPI_SUCCESS};

    if (ret) {
        Logger::log(std::to_string(rank) + " succesfully started async receive.");
    }

    else {
        Logger::log(std::to_string(rank) + std::to_string(rank) + " failed to start async receive");
    }

    return ret;
}

void Node::handle(const Message&msg) {
    switch (msg.tag()) {
        case HELLO:
            Logger::log("Handling hello from " + std::to_string(msg.source()) + ".");
            handleHello(msg);
            break;
        case GOODBYE:
            Logger::log("Handling goodbye from " + std::to_string(msg.source()) + ".");
            handleGoodbye(msg);
            break;
        case ACKNOWLEDGE:
            Logger::log("Handling acknowledge from " + std::to_string(msg.source()) + ".");
            handleAcknowledge(msg);
            break;
        case WORK:
            Logger::log("Handling work from " + std::to_string(msg.source()) + ".");
            handleWork(msg);
            break;
        default:
            throw;
    }
}

int Node::getRank() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}

int Node::getWorldSize() {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return size;
}

bool Node::sendMessage(const Message &msg) const {
    bool ret{MPI_Send(msg.buf(), msg.count(), msg.datatype(), msg.dest(), msg.tag(), MPI_COMM_WORLD) == MPI_SUCCESS};

    if (ret) {
        Logger::log(std::to_string(rank) + " successfully sent message to " + std::to_string(msg.dest()) + " type: " + std::to_string(msg.tag()));
    }

    else {
        Logger::log(std::to_string(rank) + " failed to send message to " + std::to_string(msg.dest()));
    }

    return ret;
}

bool Node::messageCheck() {
    int flag, ret{MPI_Test(&request, &flag, &status)};

    if ((ret == MPI_SUCCESS) && flag) {
        msgBuf.parseMPIStatus(status);

        Logger::log(std::to_string(rank) + " successfully received message from " + std::to_string(msgBuf.source()));

        startListen(); // restart async listen on successful message receive
    }

    else if ((ret == MPI_SUCCESS) && !flag) {
        Logger::log(std::to_string(rank) + " succesfully checked messages but none found");
    }

    else {
        Logger::log(std::to_string(rank) + " message check fail");
    }

    return (ret==MPI_SUCCESS) && flag;
}