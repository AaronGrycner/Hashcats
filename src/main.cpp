#include "../test/test.h"

// for this preliminary version, a hostfile and a wordlist should be placed in the same directory as the executable

// TODO
// -- add ssh setup
// -- add Host discovery
// -- add error handling

#define TEST

int main()
{

#ifdef TEST
    messageTest();
#endif

    return 0;
}


