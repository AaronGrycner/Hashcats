#include "Master.h"
#include "Apprentice.h"

#include "utils.h"

#include <mpi.h>

// for this preliminary version, a hostfile and a wordlist should be placed in the same directory as the executable

// TODO
// -- add environment setup to the makefile
// -- add host discovery
// -- add robust messenging
// -- add logging
// -- add error handling

int main(int argc, char *argv[])
{
    Node* node;

    MPI_Init(&argc, &argv);

    if (utils::getRank() == 0)
    {
        node = new Master();
        node->run();
    }

    else
    {
        node = new Apprentice();
        node->run();
    }

    MPI_Finalize();

    delete node;

    return 0;
}
