//
// Created by aaron on 3/1/24.
//

#ifndef MESSAGES_H
#define MESSAGES_H

#include <mpi.h>
#include <vector>
#include <string>

/*
 * This file contains the messages that are sent between the master and the apprentices.
 */

namespace messages {

    enum MessageTag {
        HELLO, // sent by the master to apprentices to see if they are online
        ACKNOWLEDGE, // acknowledges hello from apprentice to master
    };

    class Message {
    protected:
        void *_buf;
        int _count;
        MPI_Datatype _datatype;
        int _dest;
        int _tag;

    public:
        Message()=default;

        [[nodiscard]] void* buf() const { return _buf; }
        [[nodiscard]] int count() const { return _count; }
        [[nodiscard]] MPI_Datatype datatype() const { return _datatype; }
        [[nodiscard]] int dest() const { return _dest; }
        [[nodiscard]] int tag() const { return _tag; }
    };

    class Hello : public Message {
    public:
        explicit Hello(const int &rank) : Message() {
            _buf = nullptr;
            _count = 0;
            _datatype = MPI_INT;
            _dest = rank;
            _tag = HELLO;
        }
    };

    class Acknowledge : public Message {
    public:
        explicit Acknowledge() : Message() {
            _buf = nullptr;
            _count = 0;
            _datatype = MPI_INT;
            _dest = 0;
            _tag = ACKNOWLEDGE;
        }
    };
}

#endif //MESSAGES_H
