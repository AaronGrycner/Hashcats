#include "Master.h"

#include <unistd.h>

void Master::checkApprentices() {

}

void Master::run() {
    while (!done) {
        Message msg = listen();
        handle(msg);
    }
}

void Master::handleAcknowledge(const Message &msg) {

}

void Master::handleHello(const Message &msg) {

}

void Master::handleGoodbye(const Message &msg) {

}
