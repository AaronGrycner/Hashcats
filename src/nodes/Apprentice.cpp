#include "Apprentice.h"
#include "Message.h"
#include "Logger.h" // Ensure the Logger class is included
#include "utils.h" // Ensure the utils namespace is included

Apprentice::~Apprentice() {
    Logger::log("Apprentice " + std::to_string(rank) + " exiting...");
}

void Apprentice::handleAcknowledge(const Message &msg) {
    Logger::log("Apprentice::handleAcknowledge - Acknowledgement received.");
}

void Apprentice::handleGoodbye(const Message &msg) {
    done = true;
    Logger::log("Apprentice::handleGoodbye - Marking as done.");
}

void Apprentice::handleHello(const Message &msg) {
    sendMessage(Message(msg.source(), ACKNOWLEDGE));
    Logger::log("Apprentice::handleHello - Responding with ACKNOWLEDGE.");
}

void Apprentice::handleWork(const Message &msg) {
    sendMessage(Message(msg.source(), ACKNOWLEDGE));
    Logger::log("Apprentice::handleWork - Responding with ACKNOWLEDGE.");

    work = msg.getWork();
    done = true;
}

void Apprentice::run() {
    while (!done) {
        if (messageCheck()) {
            handle(msgBuf);
        }
        utils::sleep(500);
    }
    writeWork();
}

void Apprentice::writeWork() {
    std::ofstream f(std::to_string(rank) + ".txt");

    for(const auto &word : work) {
        f << word << '\n';
    }
}
