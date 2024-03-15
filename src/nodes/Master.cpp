#include "Master.h"
#include "Apprentice.h"

#include "Message.h"
#include "Logger.h"
#include "utils.h"

Master::Master() {
    apprenticeList.resize(worldsize);

    // set ranks
    for (int i{1}; i < worldsize; ++i) {
        Logger::log("Adding apprentice with rank " + std::to_string(i));
        apprenticeList.at(i).rank = i;
    }
}

void Master::pingApprentices() {
    for (ApprenticeInfo apprentice : apprenticeList) {
        Logger::log("Apprentice rank: " + std::to_string(apprentice.rank) + ", active: " + std::to_string(apprentice.active) + ", rank: " + std::to_string(apprentice.rank) + ".");
        if (apprentice.rank != 0) {
            Logger::log("Pinging apprentice with rank " + std::to_string(apprentice.rank));
            sendMessage(Message(apprentice.rank, HELLO));
        }
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

void Master::run() {
    pingApprentices();
    Message tmp;

    while(!done) {
        if (listen(tmp)) {
            handle(tmp);
        }

        done = true;

        for (auto apprentice : apprenticeList) {
            if (!apprentice.active) {
                done = false;
                break;
            }
        }

        utils::sleep(500);
    }
}
