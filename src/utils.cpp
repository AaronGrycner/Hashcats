#include "utils.h"
#include "defs.h"

#include <fstream>

#include <mpi/mpi.h>

namespace utils {
    int getRank()
    {
        return MPI_Comm_rank(MPI_COMM_WORLD, nullptr);
    }

    int getWorldSize()
    {
        return MPI_Comm_size(MPI_COMM_WORLD, nullptr);
    }
};