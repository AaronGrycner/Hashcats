#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "Work.h"

#include <queue>

class Master final : public Node {
private:
    Work work;
    static void sendHello(const int &dest);
    void listen();

    std::queue<messages::Message> messages; // message queue

public:
    explicit Master(const std::string &listname);
    void run() override;

};

#endif