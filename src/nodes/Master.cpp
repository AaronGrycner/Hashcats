#include "Master.h"

#include "defs.h"

#include <stdexcept>
#include <iostream>

Master::Master() : work(WORDLIST)
{
}

void Master::run()
{
    if (worldsize < 2) {
        throw std::runtime_error("Worldsize must be at least 2");
    }

    work.split(worldsize); // Split the work into the number of apprentices


}

void Master::readWordlist()
{
    
}