#include "Master.h"

#include <unistd.h>

void Master::pingApprentices() {
    MessageData data;

    for (int i{1}; i < worldsize + 1; ++i) {
        startListen(data);
        sendMessage(messages::hello(i));
        sleep(1);
        if (checkResponse(data)) {
            std::cout << "Apprentice at rank " + std::to_string(i) + " found!";
        }
    }
}


void Master::run()
{
    pingApprentices();
}