//
// Created by aaron on 3/1/24.
//

#ifndef MASTERMESSENGER_H
#define MASTERMESSENGER_H

#include "Messenger.h"

#include <vector>

class MasterMessenger final : public Messenger {
private:
    void listen() override;

public:
    MasterMessenger()=default;
    ~MasterMessenger()override=default;

    void hello(const int &rank);
    void goodbye(); // will always be sent to broadcast
    void sendWork(const int &rank, const std::vector<std::string> &work);
    std::vector<std::string> receiveResults();
};



#endif //MASTERMESSENGER_H
