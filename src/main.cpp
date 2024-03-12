
#include "../test/messagingtest.h"

// for this preliminary version, a hostfile and a wordlist should be placed in the same directory as the executable

// TODO
// -- add environment setup to the makefile
// -- add host discovery
// -- add robust messenging
// -- add logging
// -- add error handling

int main(int argc, char *argv[])
{
    MPI_Init(nullptr, nullptr);

    messageTest();

    MPI_Finalize();

    return 0;
}
