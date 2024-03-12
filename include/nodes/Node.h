#ifndef NODE_H
#define NODE_H

#include <queue>

#include "Message.h"

class Node {
protected:
    int rank, worldsize;

    static void startListen(messages::MessageData &msg);
    static bool checkResponse(messages::MessageData &data);
    static void sendMessage(const messages::Message &msg);

public:
    Node();
    virtual ~Node() = default;

    virtual void run()=0;
};

#endif