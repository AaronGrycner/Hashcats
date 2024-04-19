#include "Node.h"

#include "Logger/Logger.h"
#include "Messages.h"
#include "utils.h"

using namespace Messages;

Node::Node() {
    // get mpi rank and world sizes
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Logger::log("Node rank: " + std::to_string(rank) + ", world size: " + std::to_string(worldsize) + ".");
}

Node::~Node() = default;
