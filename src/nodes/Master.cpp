#include "Master.h"

#include <unistd.h>

#include "Apprentice.h"

Master::Master() {
    apprenticeList.resize(worldsize);
    int i{};

    // set ranks
    for (ApprenticeInfo apprentice : apprenticeList) {
        apprentice.rank = i;
        ++i;
    }
}

void Master::pingApprentices() {
    for (ApprenticeInfo apprentice : apprenticeList) {
        Message(apprentice.rank, HELLO);
    }
}
void Master::handleAcknowledge(const Message &msg) {
    apprenticeList.at(msg.source()).active = true;
}

void Master::handleHello(const Message &msg) {
    apprenticeList.at(msg.source()).active = true;
}

void Master::handleGoodbye(const Message &msg) {
    apprenticeList.at(msg.source()).active = false;
}
