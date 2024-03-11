//
// Created by aaron on 3/7/24.
//

#ifndef MESSENGER_H
#define MESSENGER_H

#include <queue>

#include "Messages.h"

using namespace messages;

class Messenger {
private:
    std::queue<Message> recvQueue, sendQueue;
    bool _gotMail{false}; // true if there are messages in recvQueue, false if not

public:
    Messenger();

    bool gotMail() const { return _gotMail; }

    void sendMessage(const Message &msg);
    Message getMessage(); // gets next message off the messagequeue

};



#endif //MESSENGER_H
