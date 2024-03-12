//
// Created by aaron on 3/7/24.
//

#ifndef MESSENGER_H
#define MESSENGER_H

#include <atomic>
#include <thread>

#include "Queue.h"

using namespace messages;

class Messenger {
private:
    MessageQueue queue;
    bool _gotMail{false}; // true if there are messages in recvQueue, false if not
    std::atomic<bool> done{false};

    void listen();

public:
    Messenger();

    [[nodiscard]] bool gotMail() const { return _gotMail; }

    void sendMessage(const Message &msg);
    Message getNextMessage(); // gets next message off the messagequeue

};

#endif //MESSENGER_H
