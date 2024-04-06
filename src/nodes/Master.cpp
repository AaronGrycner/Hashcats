#include "Master.h"
#include "Apprentice.h"

#include "Message.h"
#include "Logger.h"
#include "utils.h"
#include "Exceptions.h"

Master::Master() {
    apprenticeList.resize(worldsize);

    // set ranks
    for (int i{1}; i < worldsize; ++i) {
        Logger::log("Adding apprentice with rank " + std::to_string(i));
        apprenticeList.at(i).rank = i;
    }
}

Master::~Master() {
    Logger::log("Master exiting...");
}

void Master::pingApprentices() {
    utils::sleep(500); // sleep to allow time for apprentices to begin listening

    for (ApprenticeInfo apprentice : apprenticeList) {
        if (apprentice.rank != 0) {
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
    Work w;

    w.emplace_back("hi!!!!!!");

    while(!done) {
        if (messageCheck()) {
            handle(msgBuf);
            done = true;
        }

        utils::sleep(500);
    }

    sendMessage(Message(1, WORK, w));
    utils::sleep(500);

    sendMessage(Message(1, GOODBYE));
    utils::sleep(500);

}

void Master::handleWork(const Message &msg) {
    // not needed
}

