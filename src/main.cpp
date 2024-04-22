#include "Master.h"
#include "Apprentice.h"
#include "utils.h"
#include "Logger.h"

// TODO
// -- add environment setup to the makefile
// -- add host discovery
// -- add logging
// -- add error handling
// -- add shared_pointer memory management

#define TEST

int main()
{
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

    return 0;
}

