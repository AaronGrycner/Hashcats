#ifndef NODE_H
#define NODE_H

class Message;

class Node {
protected:
    int rank, worldsize;
    bool done{false};

    virtual void handleHello(const Message &msg)=0;
    virtual void handleAcknowledge(const Message &msg)=0;
    virtual void handleGoodbye(const Message &msg)=0;

    static void sleep(const int &time);

public:
    Node();
    virtual ~Node();

    bool listen(Message &msg);
    void sendMessage(const Message &msg);

    static int getRank();
    static int getWorldSize();

    static void init();
    virtual void run()=0;

    void handle(const Message &msg);

};

#endif