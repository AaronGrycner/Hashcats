#ifndef TEST_H
#define TEST_H

#include "Master.h"
#include "Apprentice.h"
#include "utils.h"
#include "init.h"
#include "Logger.h"
#include "Messages.h"

void messageTest() {

    Logger::init();

    init::init();

    if (Node::getRank() == 0) {
        Logger::log("i am the master!");
        Master node;

        if (Node::getWorldSize() > 1) {
            Logger::log("Multi thread MPI init success, world size: " + std::to_string(Node::getWorldSize()) + ", rank: " + std::to_string(Node::getRank()) + ".");
        }

        else {
            Logger::log("MPI Failed to start multiple threads.");
        }
        node.run();

    }

    else {
        Logger::log("i am the apprentice!");
        Apprentice node;

        node.run();

    }

    MPI_Finalize();
}

void networkTest() {

}

#endif