#ifndef TEST_H
#define TEST_H

#include "Master.h"
#include "Apprentice.h"

inline void messageTest() {
    int provided, rank, size;

    MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &provided);

    if (rank == 0) {
        Master mast;
        const Message msg(1, HELLO);

        std::cout << "Multi thread MPI init success, world size: " << size << std::endl;

        Master::sendMessage(Message(1, HELLO));
    }

    else if (rank == 1) {
        Apprentice appr;
        Message msg;

        if (Apprentice::listen(msg)) {
            std::cout << "Message receive success!\n";
        }
        else {
            std::cout << "Message receive fail.";
        }
    }

    MPI_Finalize();

}

#endif