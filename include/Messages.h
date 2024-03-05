//
// Created by aaron on 3/1/24.
//

#ifndef MESSAGES_H
#define MESSAGES_H

#include "defs.h"

#include <mpi.h>
#include <vector>
#include <string>

/*
 * This file contains the messages that are sent between the master and the apprentices.
 */

namespace messages {

    // struct to store temporary data before creation of a message object
    class messageData {
    public:
        void* buf{};
        int count{BUFFER_SIZE};
        MPI_Datatype datatype{};
        int dest{-1};
        int source{-1};
        int tag{};
        int flag{};
        MPI_Request request{};
        MPI_Status status{};
    };

    enum MessageTag {
        HELLO, // sent by the master to apprentices to see if they are online
        ACKNOWLEDGE, // acknowledges hello from apprentice to master
    };

    class Message {
    protected:
        void* _buf{};
        int _count{BUFFER_SIZE};
        MPI_Datatype _datatype{};
        int _source{};
        int _tag{};

    public:
        explicit Message()=default;

        // each returns a pointer to their object
        [[nodiscard]] void* buf() const { return _buf; }
        [[nodiscard]] int count() const { return _count; }
        [[nodiscard]] MPI_Datatype datatype() const { return _datatype; }
        [[nodiscard]] int source() const { return _source; }
        [[nodiscard]] int tag() const { return _tag; }
    };

    class Hello : public Message {
    public:
        explicit Hello(const int &rank) : Message() {
            _buf = nullptr;
            _count = 0;
            _datatype = MPI_INT;
            _source = rank;
            _tag = HELLO;
        }
        Hello();

    };


    class Acknowledge : public Message {
    public:
        explicit Acknowledge() {
            _buf = nullptr;
            _count = 0;
            _datatype = MPI_INT();
            _source = nullptr;
            _tag = ACKNOWLEDGE();
        }
    };
}

#endif //MESSAGES_H
