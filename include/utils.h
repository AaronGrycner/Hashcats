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

    inline int get_world_size() {
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        return world_size;
    }

    inline int get_rank() {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        return rank;
    }

    inline void finalize() {
        MPI_Finalize();
    }

}

#endif // UTILS_H
