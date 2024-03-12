#include "Apprentice.h"

#include <unistd.h>

void Apprentice::handleAcknowledge(const Message &msg) {
    // nothing to do
}

void Apprentice::handleGoodbye(const Message &msg) {
    done = true;
}

void Apprentice::handleHello(const Message &msg) {
    Message(0, ACKNOWLEDGE).send();
}