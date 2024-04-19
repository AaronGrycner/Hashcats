//
// Created by aaron on 4/17/24.
//

#ifndef HASHCATS_MESSAGEFACTORY_H
#define HASHCATS_MESSAGEFACTORY_H


// creates a desired message type or takes an MPI_Status and returns the appropriate message type

// int MPI_Send(const void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);

#include "Messages.h"

namespace Messages {

    class MessageFactory {
    public:
        static std::shared_ptr<Messages::Message> parse_MPI_Status(const MPI_Status &status, const std::string &buffer);

    };

} // Messages

#endif //HASHCATS_MESSAGEFACTORY_H
