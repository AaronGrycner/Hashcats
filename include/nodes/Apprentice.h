#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:
    Work work;

    ApprenticeMessenger messenger;

    void handleAcknowledge(const Message &msg) override;
    void handleGoodbye(const Message &msg) override;
    void handleHello(const Message &msg) override;
    void handleWork(const Message &msg) override;

    void writeWork();

public:
    Apprentice()=default;
    ~Apprentice() override;
    void run() override;

};

#endif