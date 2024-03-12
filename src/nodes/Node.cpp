#include "Node.h"

#include "utils.h"

#include <thread>

Node::Node() : rank(utils::getRank()), worldsize(utils::getWorldSize())
{
}

void Node::sleep(const int &time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void Node::handle(const Message &msg) {
    switch (msg.tag()) {
        case HELLO:
            handleHello(msg);
        break;
        case GOODBYE:
            handleGoodbye(msg);
        break;
        case ACKNOWLEDGE:
            handleAcknowledge(msg);
        break;
        default:
            throw;
    }
}

// sends message, checks for response
bool Node::send(const Message &msg) {
    int flag{};
    MPI_Request request;
    MPI_Status status;

    msg.send();

    MPI_Irecv(nullptr, 0, msg.datatype(), msg.dest(), msg.tag(), MPI_COMM_WORLD, &request);

    sleep(500);

    return MPI_Test(&request, &flag, &status);
}

// listens for message, returns true if any message has been received
bool Node::listen() {
    MPI_Request request;
    MPI_Status status;
    int flag{};

    MPI_Irecv(nullptr, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request);

    sleep(500);

    if (MPI_Test(&request, &flag, &status)) {
        handle(Message(status));
    }

    return flag;
}