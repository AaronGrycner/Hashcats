#ifndef MESSAGES_H
#define MESSAGES_H

#include "Message.h"

#include <string>
#include <thread>
#include <vector>

class Messenger {
protected:
    void sendMessage(Message msg);

public:
    Messenger()=default;
    void init();
};








#endif