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
        MPI_Init(nullptr, nullptr);
    }

    inline void finalize() {
        MPI_Finalize();
    }

}

#endif // UTILS_H
