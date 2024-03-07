//
// Created by aaron on 3/7/24.
//

#include "Messages.h"

using namespace messages;


// constructor for writing messages to be sent
Hello::Hello(const int &destination) {
    MessageData _data;
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.dest = destination;
    _data.tag = HELLO;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}

// constructor for writing messages to be sent
Acknowledge::Acknowledge() {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.dest = 0;
    _data.tag = ACKNOWLEDGE;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}

// constructor for writing messages to be sent
Goodbye::Goodbye(const int &destination) {
    _data.buf = nullptr;
    _data.count = 0;
    _data.datatype = MPI_INT;
    _data.dest = destination;
    _data.tag = ACKNOWLEDGE;
    MPI_Comm_rank(MPI_COMM_WORLD, &_data.source);
}
