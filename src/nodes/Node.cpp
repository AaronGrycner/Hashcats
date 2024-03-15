#include "Node.h"

#include "Log/Logger.h"
#include "Message.h"
#include "utils.h"

Node::Node() {
    // get mpi rank and world size
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

Node::~Node() {
    MPI_Finalize();
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
        default:
            throw;
    }
}

// listens for message, returns true if any message has been received
bool Node::listen(Message&msg) {
    MPI_Request request;
    MPI_Status status;
    int flag;

    Logger::log("Beginning async receive...");
    MPI_Irecv(nullptr, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);

    int ret = MPI_Test(&request, &flag, &status);

    if (ret == MPI_SUCCESS && flag) {
        Logger::log(
            "Message received from: " + std::to_string(status.MPI_SOURCE) + " with tag: " +
            std::to_string(status.MPI_TAG));
        msg = Message(status);
        return true;
    }

    else {
        Logger::log("MPI_Test failed with error code: " + std::to_string(ret) + ".");
        return false;
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

void Node::sendMessage(const Message&msg) {
    MPI_Send(msg.buf(), msg.count(), msg.datatype(), msg.dest(), msg.tag(), MPI_COMM_WORLD);
}
