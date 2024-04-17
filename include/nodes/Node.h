#ifndef NODE_H
#define NODE_H

#include <mpi.h>

#include "defs.h"
#include "Messages.h"

class Node {
protected:
    int rank{}, worldsize{};
    bool done{false};

    MPI_Request request;
    MPI_Status status;
    Message msgBuf;

    virtual void handleHello(const Message &msg)=0;
    virtual void handleAcknowledge(const Message &msg)=0;
    virtual void handleGoodbye(const Message &msg)=0;
    virtual void handleWork(const Message &msg)=0;

public:
    Node();
    virtual ~Node()=0;

    bool startListen();

    bool sendMessage(const Message &msg) const;

    static int getRank();
    static int getWorldSize();

    virtual void run()=0;

    void handle(const Message &msg);

    bool messageCheck();

};

#endif