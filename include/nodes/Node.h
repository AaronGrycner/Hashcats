#ifndef NODE_H
#define NODE_H

#include <queue>

#include "Message.h"


class Node {
protected:
    int rank, worldsize;
    bool done{false};

    virtual void handleHello(const Message &msg)=0;
    virtual void handleAcknowledge(const Message &msg)=0;
    virtual void handleGoodbye(const Message &msg)=0;

    void handle(const Message &msg);

public:
    Node();
    virtual ~Node() = default;

    virtual void run()=0;

    Message listen();

};

#endif