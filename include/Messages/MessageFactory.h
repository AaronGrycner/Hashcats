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

        static HelloMessage create_hello(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
        static AcknowledgeMessage create_acknowledge(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
        static GoodbyeMessage create_goodbye(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
        static PcapMessage create_pcap(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
        static WordlistMessage create_wordlist(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);

    };

} // Messages

#endif //HASHCATS_MESSAGEFACTORY_H
