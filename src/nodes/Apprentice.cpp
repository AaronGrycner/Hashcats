#include "Apprentice.h"

#include <unistd.h>

void Apprentice::run()
{
    MessageData data;
    startListen(data);

    while (true) {
        if (checkResponse(data)) {
            sendMessage(messages::acknowledge());
            break;
        }
        sleep(1);
    }
}

Apprentice::~Apprentice() = default;