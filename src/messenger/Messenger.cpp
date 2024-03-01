#include "messenger.h"

#include <mpi.h>

// general function for sending messages with no payload
void Messenger::sendMessage(const int &tag, const int &rank)
{
    MPI_Send(0, 1, MPI_INT, rank, tag, MPI_COMM_WORLD);
}

// general function for sending messages with a payload
void Messenger::sendMessage(const int &tag, const int &rank, const std::string &message)
{
    MPI_Send(0, 1, MPI_INT, rank, tag, MPI_COMM_WORLD);
}

// general function for sending broadcast messages to all nodes
void Messenger::sendBroadcast(const int &tag)
{
    MPI_Bcast(0, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

// function for sending a hello message to a specific node
void MasterMessenger::hello(const int &rank)
{
    sendMessage(HELLO, rank);
}

// function for sending a goodbye message to all nodes
void MasterMessenger::goodbye()
{
    sendBroadcast(GOODBYE);
}

// function for sending an acknowledge message to the master
void ApprenticeMessenger::sendResultFound()
{
    sendBroadcast(RESULT_FOUND);
}
