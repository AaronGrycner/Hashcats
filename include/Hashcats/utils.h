//
// Created by aaron on 3/14/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <thread>
#include <chrono>
#include <mpi.h>

namespace utils {

    inline void sleep(const int &ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    inline void init() {
        int provided;
        MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &provided);
    }

    inline void finalize() {
        MPI_Finalize();
    }

}

#endif // UTILS_H
