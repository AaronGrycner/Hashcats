#include "Master.h"
#include "Apprentice.h"

#include "Message.h"
#include "Logger.h"

Master::Master() {
    apprenticeList.resize(worldsize);
    int i{};

    // set ranks
    for (ApprenticeInfo apprentice : apprenticeList) {
        Logger::log("Adding apprentice with rank " + std::to_string(i));
        apprentice.rank = i;
        ++i;
    }
}

void Master::pingApprentices() {
    for (ApprenticeInfo apprentice : apprenticeList) {
        Logger::log("Pinging apprentice with rank " + std::to_string(apprentice.rank));
        sendMessage(Message(apprentice.rank, HELLO));
    }
}

void Master::handleAcknowledge(const Message &msg) {
    Logger::log("Master::handleAcknowledge - Acknowledgement received from " + std::to_string(msg.source()));
    apprenticeList.at(msg.source()).active = true;
}

void Master::handleHello(const Message &msg) {
    apprenticeList.at(msg.source()).active = true;
    Logger::log("Master::handleHello - Hello received from " + std::to_string(msg.source()));
    sendMessage(Message(msg.source(), ACKNOWLEDGE));
}

void Master::handleGoodbye(const Message &msg) {
    apprenticeList.at(msg.source()).active = false;
    Logger::log("Master::handleGoodbye - Goodbye received from " + std::to_string(msg.source()));
}
