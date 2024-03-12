#include "Node.h"

#include "utils.h"

Node::Node() : rank(utils::getRank()), worldsize(utils::getWorldSize())
{
}

void Node::handle(const Message &msg) {
    switch (msg.type()) {
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

Message Node::listen() {
    void *buf;
    MPI_Status status;

    MPI_Recv(buf, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    return Message(status);
}