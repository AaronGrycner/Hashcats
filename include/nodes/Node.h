#ifndef NODE_H
#define NODE_H

#include <mpi.h>
#include <memory>

#include "defs.h"
#include "Messages.h"
#include "Messenger.h"

class Node {
protected:
    std::unique_ptr<char[]> buffer{new char[BUFFER_SIZE]};

    int rank{}, worldsize{};
    bool done{false};

    MPI_Request request{};
    MPI_Status status{};

    Messenger messenger;

    virtual void handleHello(const Messages::HelloMessage &msg)=0;
    virtual void handleAcknowledge(const Messages::AcknowledgeMessage &msg)=0;
    virtual void handleGoodbye(const Messages::GoodbyeMessage &msg)=0;
    virtual void handleWordlist(const Messages::WordlistMessage &msg)=0;
    virtual void handlePcap(const Messages::PcapMessage &msg)=0;

public:
    Node();
    virtual ~Node()=0;

    [[nodiscard]] int getRank() const { return rank; }
    [[nodiscard]] int getWorldSize() const { return worldsize; }

    virtual void run()=0;

};

#endif