//
// Created by aaron on 3/7/24.
//

#include "Message.h"

Message::Message(const int &dest, const MessageType &type) : _dest(dest), _tag(type) {
    MPI_Comm_rank(MPI_COMM_WORLD, &_source);
}

Message::Message(const MPI_Status &status) : _status(status) {
    parseMPIStatus();
}

void Message::parseMPIStatus() {
    MPI_Get_count(&_status, _datatype, &_count);
    _source = _status.MPI_SOURCE;
    _error = _status.MPI_ERROR;
    _tag = _status.MPI_TAG;
}

int Message::send() const {
    return MPI_Send(_buf, _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
}

