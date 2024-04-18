#ifndef TEST_H
#define TEST_H

#include "Master.h"
#include "Apprentice.h"
#include "utils.h"
#include "Logger.h"
#include "Messages.h"

void messageTest() {

    Logger::init();

    utils::init();

    if (utils::get_rank() == 0) {
        Logger::log("i am the master!");
        Master node;

        if (utils::get_world_size() > 1) {
            Logger::log("Multi thread MPI init success, world size: " + std::to_string(utils::get_world_size()) + ", rank: " + std::to_string(utils::get_rank()) + ".");
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