//
// Created by aaron on 3/7/24.
//

#include "Message.h"

using namespace messages;

int Message::send() const {
    return MPI_Send(_data.buf, _data.count, _data.datatype, _data.dest, _data.tag, MPI_COMM_WORLD);
}

Hello::Hello(const int &dest) : Message(dest) {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.tag = HELLO;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}

Acknowledge::Acknowledge(const int &dest) : Message(dest) {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.tag = ACKNOWLEDGE;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}

Goodbye::Goodbye(const int &dest) : Message(dest) {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.tag = GOODBYE;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}
