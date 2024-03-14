#ifndef NODE_H
#define NODE_H

#include "Message.h"

class Node {
protected:
    int rank, worldsize;
    bool done{false};

    virtual void handleHello(const Message &msg)=0;
    virtual void handleAcknowledge(const Message &msg)=0;
    virtual void handleGoodbye(const Message &msg)=0;

    static void sleep(const int &time);

    void handle(const Message &msg);

public:
    Node();
    virtual ~Node() = default;

    static bool listen(Message &msg);
    static void sendMessage(const Message &msg);

    int getRank() const { return rank; }
    int getWorldSize() const {return worldsize; }

};

#endif