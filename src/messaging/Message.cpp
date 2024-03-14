//
// Created by aaron on 3/7/24.
//

#include "Message.h"


Message::Message(const int &dest, const MessageType &type) : _dest(dest), _tag(type) {
    MPI_Comm_rank(MPI_COMM_WORLD, &_source);
}

Message::Message(const MPI_Status &status) {
    parseMPIStatus(status);
}

void Message::parseMPIStatus(const MPI_Status &status) {
    MPI_Get_count(&status, _datatype, &_count);
    _source = status.MPI_SOURCE;
    _error = status.MPI_ERROR;
    _tag = status.MPI_TAG;
}

