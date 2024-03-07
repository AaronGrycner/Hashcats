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


namespace messages {
    enum MessageTag {
        HELLO, // sent by the master to apprentices to see if they are online
        ACKNOWLEDGE, // acknowledges hello from apprentice to master
    };

    struct MessageData {
        void *buf;
        int count;
        MPI_Datatype datatype;
        int dest;
        int source;
        int tag;
        int flag;
        MPI_Request request;
        MPI_Status status;
    };

    class Message {
    protected:
        MessageData _data;

    public:
        Message();

        explicit Message(const MessageData &data) : _data(data) { }

        [[nodiscard]] void *buf() const { return _data.buf; }
        [[nodiscard]] int count() const { return _data.count; }
        [[nodiscard]] MPI_Datatype datatype() const { return _data.datatype; }
        [[nodiscard]] int dest() const { return _data.dest; }
        [[nodiscard]] int source() const { return _data.source; }
        [[nodiscard]] int tag() const { return _data.tag; }
        [[nodiscard]] int flag() const { return _data.flag; }
        [[nodiscard]] MPI_Request request() const { return _data.request; }
        [[nodiscard]] MPI_Status status() const { return _data.status; }
    };

    class Hello : public Message {
    public:
        explicit Hello(const int &destination); // constructor for writing messages to be sent
        explicit Hello(const MessageData &data) { _data = data; } // constuctor for reading in received messages
    };

    class Acknowledge : public Message {
    public:
        Acknowledge(); // constructor for writing messages to be sent
        explicit Acknowledge(const MessageData &data) { _data = data; } // constuctor for reading in received messages
    };

    class Goodbye : public Message {
    public:
        explicit Goodbye(const int &destination); // constructor for writing messages to be sent
        explicit Goodbye(const MessageData &data) { _data = data; } // constuctor for reading in received messages
    };
}


#endif //MESSAGES_H
