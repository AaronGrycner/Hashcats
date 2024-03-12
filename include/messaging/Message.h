//
// Created by aaron on 3/1/24.
//

#ifndef MESSAGES_H
#define MESSAGES_H

#include "defs.h"

#include <mpi.h>

/*
 * This file contains the messages that are sent between the master and the apprentices.
 */


enum MessageType {
    HELLO, // sent by the master to apprentices to see if they are online
    ACKNOWLEDGE, // acknowledges hello from apprentice to master
    GOODBYE // Goodbye
};

class Message {
private:
    void *_buf{nullptr};
    int _count{};
    MPI_Datatype _datatype{MPI_CHAR};
    int _dest{};
    int _source{};
    int _tag{};
    int _error{};
    MPI_Status _status{};
    MPI_Request _request{};

    void parseMPIStatus();

public:
    Message()=default;
    Message(const MPI_Status &status);

    explicit Message(const int &dest, const MessageType &type);

    int send() const;

    void *buf() const { return _buf; }
    int count() const { return _count; }
    MPI_Datatype datatype() const { return _datatype; }
    int dest() const { return _dest; }
    int source() const { return _source; }
    int type() const { return _tag; }
    int error() const { return _error; }
    MPI_Request request() const { return _request; }
    MPI_Status status() const { return _status; }
};


#endif //MESSAGES_H
