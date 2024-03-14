#include "Node.h"

#include <thread>

Node::Node() : rank(getRank()), worldsize(getWorldSize())
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

// listens for message, returns true if any message has been received
bool Node::listen(Message &msg) {
    MPI_Request request;
    MPI_Status status;

    if (MPI_Recv(nullptr, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status) == MPI_SUCCESS) {
        msg = Message(status);
        return true;
    }

    return false;
}

int Node::getRank()
{
    return MPI_Comm_rank(MPI_COMM_WORLD, nullptr);
}

int Node::getWorldSize()
{
    return MPI_Comm_size(MPI_COMM_WORLD, nullptr);
}

void Node::sendMessage(const Message &msg) {
    MPI_Send(msg.buf(), msg.count(), msg.datatype(), msg.dest(), msg.tag(), MPI_COMM_WORLD);
}