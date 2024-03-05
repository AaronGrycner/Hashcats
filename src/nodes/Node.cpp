#include "Node.h"

#include "utils.h"

Node::Node() : rank(utils::getRank()), worldsize(utils::getWorldSize()), request(nullptr), data(new messageData())
{
}

void Node::listen() {

    MPI_Irecv(
        data->buf,
        data->count,
        data->datatype,
        MPI_ANY_SOURCE,
        MPI_ANY_TAG,
        MPI_COMM_WORLD,
        &data->request
        );

    MPI_Test(&data->request,
        &data->flag,
        &data->status);

    // read data from request if message was received
    if (data->flag) {
        data->source = data->status.MPI_SOURCE;
        data->tag = data->status.MPI_TAG;
    }
}

Node::~Node()
{
    delete data;
}