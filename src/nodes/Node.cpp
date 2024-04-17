#include "Node.h"

#include "Log/Logger.h"
#include "Messages.h"
#include "utils.h"
#include "Work.h"

using namespace Messages;

Node::Node() {
    // get mpi rank and world sizes
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (startListen()) {
        Logger::log("Node rank: " + std::to_string(rank) + " successfully started Irecv.");
    } else {
        Logger::log("Node rank: " + std::to_string(rank) + " failed starting Irecv.");
    }
}

Node::~Node() = default;
