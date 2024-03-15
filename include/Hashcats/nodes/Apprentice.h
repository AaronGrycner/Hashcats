#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:
    void handleAcknowledge(const Message &msg) override;
    void handleGoodbye(const Message &msg) override;
    void handleHello(const Message &msg) override;
public:
    Apprentice()=default;
    ~Apprentice()override=default;
};

#endif