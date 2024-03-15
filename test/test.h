#ifndef TEST_H
#define TEST_H

#include "Master.h"
#include "Apprentice.h"
#include "utils.h"
#include "Logger.h"
#include "Message.h"

inline void messageTest() {

    Logger::init();

    utils::init();

    if (Node::getRank() == 0) {
        Logger::log("i am the master!");
        Master node;

        Logger::log("Multi thread MPI init success, world size: " + std::to_string(Node::getWorldSize()) + ", rank: " + std::to_string(Node::getRank()) + ".");

        node.run();

    }

    else {
        Logger::log("i am the apprentice!");
        Apprentice node;

        node.run();


    }
}

#endif