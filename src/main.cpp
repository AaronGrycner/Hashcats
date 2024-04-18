#include "../test/test.h"

// for this preliminary version, a hostfile and a wordlist should be placed in the same directory as the executable

// TODO
// -- add environment setup to the makefile
// -- add host discovery
// -- add logging
// -- add error handling
// -- add shared_pointer memory management

#define TEST

int main()
{

#ifdef TEST
    messageTest();
#endif

    return 0;
}


