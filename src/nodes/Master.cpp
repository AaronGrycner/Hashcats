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

    readWordlist(WORDLIST);
}

Master::~Master() {
    Logger::log("Master exiting...");
}

void Master::pingApprentices() {
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

    while(!done) {
        if (messageCheck()) {
            handle(msgBuf);
            done = true;
        }

        utils::sleep(500);
    }

    splitWork();
    sendWork();
}

void Master::handleWork(const Message &msg) {
    // not needed
}

void Master::splitWork() {
    int i{}, appNum{worldsize-1};

    workVec.resize(worldsize - 1);

    for (const std::string &word : wordlist) {
        workVec.at(i % appNum).emplace_back(word);
        ++i;
    }
}

void Master::sendWork() {
    for (const ApprenticeInfo &apprentice : apprenticeList) {
        if (apprentice.rank != 0) {
            Logger::log("Sending work to apprentice " + std::to_string(apprentice.rank));
            sendMessage(Message(apprentice.rank, WORK, workVec.at(apprentice.rank - 1)));
        }
    }
}

void Master::readWordlist(const std::string &listname) {
    std::string temp;
    std::ifstream f(listname);

    while(f.good()) {
        getline(f, temp);
        wordlist.emplace_back(temp);
    }
}