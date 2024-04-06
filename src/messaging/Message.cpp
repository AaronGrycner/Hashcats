#include "Message.h"
#include "Logger.h"
#include <cstring>

Message::Message() : _buf(std::make_unique<char[]>(BUFFER_SIZE)) {}

Message::Message(const MPI_Status &status) : _buf(std::make_unique<char[]>(BUFFER_SIZE)) {
    parseMPIStatus(status);
}

Message::Message(const int &dest, const MessageType &type) : _dest(dest), _tag(type), _buf(std::make_unique<char[]>(BUFFER_SIZE)) {
    MPI_Comm_rank(MPI_COMM_WORLD, &_source);
}

Message::Message(const int &dest, const MessageType &type, const Work &w) : Message(dest, type) {
    work = w;
    setBuffer();
}

char* Message::buf() const { return _buf.get(); }

std::string Message::data() const {
    return std::string(_buf.get(), _count);
}

int Message::count() const { return _count; }

MPI_Datatype Message::datatype() const { return _datatype; }

int Message::dest() const { return _dest; }

int Message::source() const { return _source; }

int Message::tag() const { return _tag; }

int Message::error() const { return _error; }

void Message::setBuffer() {
    // Logic to set buffer based on 'work' or other content
    std::string temp;
    for (const auto& word : work) {
        temp.append(word);
        temp.append("\0");
    }
    _buf = std::make_unique<char[]>(temp.size());
    std::memcpy(_buf.get(), temp.data(), temp.size());
    _count = temp.size();
}

void Message::parseMPIStatus(const MPI_Status &status) {
    MPI_Get_count(&status, _datatype, &_count);
    _source = status.MPI_SOURCE;
    _error = status.MPI_ERROR;
    _tag = status.MPI_TAG;
}
