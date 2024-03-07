//
// Created by aaron on 3/7/24.
//

#include "Messages.h"

using namespace messages;

// sends the message
int Message::send() const {
    return MPI_Send(_data.buf, _data.count, _data.datatype, _data.dest, _data.tag, MPI_COMM_WORLD);
}

// constructor for writing messages to be sent
Hello::Hello(const int &dest) {
    _data.dest = dest;
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.tag = HELLO;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}

// constructor for writing messages to be sent
Acknowledge::Acknowledge(const int &dest) {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.dest = dest;
    _data.tag = ACKNOWLEDGE;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}

// constructor for writing messages to be sent
Goodbye::Goodbye(const int &dest) {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.dest = dest;
    _data.tag = ACKNOWLEDGE;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}
