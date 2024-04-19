#ifndef TEST_H
#define TEST_H

#include "Master.h"
#include "Apprentice.h"
#include "utils.h"
#include "Logger.h"
#include "Messages.h"

void messageTest() {

    Logger::init();

    MPI_Init(nullptr, nullptr);

    if (utils::get_rank() == 0) {
        Logger::log("Master node.");
        Master node;
        node.run();
    }

    else {
        Logger::log("Apprentice node.");
        Apprentice node;
        node.run();
    }

    MPI_Finalize();
}

void networkTest() {

}

#endif