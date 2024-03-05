#ifndef NODE_H
#define NODE_H

#include "Messages.h"

#include <queue>

using namespace messages;

class Node {
protected:
    int rank, worldsize;

    void listen();

    messageData *data;
    std::queue<Message> messages; // message queue

public:
    Node();
    virtual ~Node();

    virtual void run()=0;
};

#endif