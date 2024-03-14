#include <mpi/mpi.h>

#include "Master.h"
#include "Apprentice.h"

inline void messageTest() {
    int provided, rank, size;

    MPI_Init_thread(nullptr, nullptr, MPI_THREAD_MULTIPLE, &provided);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        Master mast;
        const Message msg(1, HELLO);

        std::cout << "Multi thread MPI init success, world size: " << size << std::endl;

        msg.send();
    }

    else if (rank == 1) {
        Apprentice appr;

        if (MPI_SUCCESS == MPI_Recv(nullptr, 0, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat)) {
            std::cout << "Message receive success!\n";
        }
        else {
            std::cout << "Message receive fail.";
        }
    }

    MPI_Finalize();

}