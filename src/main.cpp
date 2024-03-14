
#include "../test/test.h"



// for this preliminary version, a hostfile and a wordlist should be placed in the same directory as the executable

// TODO
// -- add environment setup to the makefile
// -- add host discovery
// -- add robust messenging
// -- add logging
// -- add error handling

#define TEST

int main(int argc, char *argv[])
{

#ifdef TEST
    messageTest();
#endif

    return 0;
}
