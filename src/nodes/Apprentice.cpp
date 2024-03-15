#include "Apprentice.h"
#include "Message.h"
#include "Logger.h" // Ensure the Logger class is included
#include "utils.h" // Ensure the utils namespace is included

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

void Apprentice::run() {
    while (!done) {
        Message tmp;
        if (listen(tmp)) {
            handle(tmp);
            done = true;
        }
        utils::sleep(500);
    }
}