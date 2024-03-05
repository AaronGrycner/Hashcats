#include "Node.h"

#include "utils.h"

Node::Node() : rank(utils::getRank()), worldsize(utils::getWorldSize())
{
}

void Node::startListen(MessageData &data) {

    MPI_Irecv(
        data.buf,
        data.count,
        data.datatype,
        MPI_ANY_SOURCE,
        MPI_ANY_TAG,
        MPI_COMM_WORLD,
        &data.request
        );
}

bool Node::checkResponse(MessageData &data) {
    MPI_Test(&data.request,
        &data.flag,
        &data.status
        );

    return data.flag;
}


void Node::sendMessage(const Message &msg) {
    MPI_Send(msg.buf(),
        msg.count(),
        msg.datatype(),
        msg.dest(),
        msg.tag(),
        MPI_COMM_WORLD
        );
}