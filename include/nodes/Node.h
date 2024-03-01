#ifndef NODE_H
#define NODE_H


class Node {
protected:
    int rank, worldsize;

public:
    Node();
    virtual ~Node()=default;

    virtual void run()=0;
};

#endif