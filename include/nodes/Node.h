#ifndef NODE_H
#define NODE_H

#include "Messenger.h"

class Node {
protected:
    int rank, worldsize;
    Messenger messenger;

public:
    Node();
    virtual ~Node()=default;

    virtual void run()=0;
};

#endif