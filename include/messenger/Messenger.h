#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

class Messenger {
protected:
    void sendMessage(const int &tag, const int &rank);
    void sendMessage(const int &tag, const int &rank, const std::string &message);
    void sendBroadcast(const int &tag);

    virtual void listen()=0;

public:
    Messenger()=default;
    virtual ~Messenger()=default;
};








#endif