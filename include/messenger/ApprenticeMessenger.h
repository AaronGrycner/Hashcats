//
// Created by aaron on 3/1/24.
//

#ifndef APPRENTICEMESSENGER_H
#define APPRENTICEMESSENGER_H

#include "Messenger.h"

class ApprenticeMessenger final : public Messenger {
private:
    void listen() override;

public:
    ApprenticeMessenger()=default;
    ~ApprenticeMessenger()override=default;

    void sendWorkResult(bool successfail); // will always be sent to master (rank 0)
    void acknowledge(); // will always be sent to master (rank 0)
    void sendResultFound(); // will always be sent to broadcast
};


#endif //APPRENTICEMESSENGER_H