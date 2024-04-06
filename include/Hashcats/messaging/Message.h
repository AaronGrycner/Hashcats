#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <string>
#include <mpi.h>
#include "Work.h"
#include "defs.h"

enum MessageType {
    HELLO, // sent by the master to apprentices to see if they are online
    ACKNOWLEDGE, // acknowledges hello from apprentice to master
    GOODBYE, // goodbye
    WORK
};

class Message {
private:
    Work work;
    std::unique_ptr<char[]> _buf;
    int _count{};

    MPI_Datatype _datatype{MPI_CHAR};
    int _dest{};
    int _source{};
    int _tag{};
    int _error{};

    void setBuffer();

public:
    Message();
    explicit Message(const MPI_Status &status);
    Message(const int &dest, const MessageType &type);
    Message(const int &dest, const MessageType &type, const Work &w);

    void parseMPIStatus(const MPI_Status &status);

    char* buf() const;
    std::string data() const;
    int count() const;
    MPI_Datatype datatype() const;
    int dest() const;
    int source() const;
    int tag() const;
    int error() const;
};

#endif // MESSAGE_H
