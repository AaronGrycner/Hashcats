#ifndef NODE_H
#define NODE_H

#include <queue>

#include "Messages.h"

using namespace messaging;

class Node {
protected:
    int rank, worldsize;

    static void startListen(MessageData &msg);
    static bool checkResponse(MessageData &data);
    static void sendMessage(const Message &msg);

public:
    Node();
    virtual ~Node() = default;

    virtual void run()=0;
};

#endif