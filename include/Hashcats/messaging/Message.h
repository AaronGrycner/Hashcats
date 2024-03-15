//
// Created by aaron on 3/1/24.
//

#ifndef MESSAGES_H
#define MESSAGES_H

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
    void *_buf;
    int _count{};
    MPI_Datatype _datatype{MPI_CHAR};
    int _dest{};
    int _source{};
    int _tag{};
    int _error{};

    void parseMPIStatus(const MPI_Status &status);

public:
    Message()=default;
    Message(const MPI_Status &status);

    explicit Message(const int &dest, const MessageType &type);

    void * buf() const { return _buf; }
    int count() const { return _count; }
    MPI_Datatype datatype() const { return _datatype; }
    int dest() const { return _dest; }
    int source() const { return _source; }
    int tag() const { return _tag; }
    int error() const { return _error; }
};


#endif //MESSAGES_H
