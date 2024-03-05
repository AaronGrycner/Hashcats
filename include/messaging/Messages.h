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

namespace messaging {

    enum MessageTag {
        HELLO, // sent by the master to apprentices to see if they are online
        ACKNOWLEDGE, // acknowledges hello from apprentice to master
    };

    class MessageData {
    public:
        void* buf{new int};
        int count{BUFFER_SIZE};
        MPI_Datatype datatype{};
        int dest{-1};
        int source{-1};
        int tag{-1};
        int flag{-1};
        MPI_Request request{};
        MPI_Status status{};
    };



    class Message {
    protected:
        MessageData _data;

    public:
        Message()=default;
        explicit Message(const MessageData &data) : _data(data) {}

        void setData(const MessageData &data) { _data = data; }

        [[nodiscard]] void* buf() const { return _data.buf; }
        [[nodiscard]] int count() const { return _data.count; }
        [[nodiscard]] MPI_Datatype datatype() const { return _data.datatype; }
        [[nodiscard]] int dest() const { return _data.dest; }
        [[nodiscard]] int source() const { return _data.source; }
        [[nodiscard]] int tag() const { return _data.tag; }
        [[nodiscard]] int flag() const { return _data.flag; }
        [[nodiscard]] MPI_Request request() const { return _data.request; }
        [[nodiscard]] MPI_Status status() const { return _data.status; }

    };

    namespace messages {
        inline Message acknowledge() {
            MessageData data;

            data.buf=nullptr;
            data.count=0;
            data.datatype=MPI_INT;
            data.dest=0;
            data.tag=ACKNOWLEDGE;

            return Message(data);
        }

        inline Message hello(const int &dest) {
            MessageData data;

            data.buf=nullptr;
            data.count=0;
            data.datatype=MPI_INT;
            data.dest=dest;
            data.tag=HELLO;

            return Message(data);
        }
    }

};



#endif //MESSAGES_H
