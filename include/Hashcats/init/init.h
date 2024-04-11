#include <chrono> // Include for time-based utilities, may be unused if not needed later
#include <mpi.h> // Include for MPI functions
#include <stdexcept> // Include for using standard exception types

#include "ssh_check.h"
#include "network_check.h"

namespace init {
    std::vector<std::string> network_list;

    // Function to initialize the application
    void init() {
        ssh_check(); // Perform SSH checks before initialization
        network_check();
        MPI_Init(nullptr, nullptr); // Initialize MPI environment
    }

    // Function to finalize the application
    void finalize() {
        MPI_Finalize(); // Finalize MPI environment
    }
}
