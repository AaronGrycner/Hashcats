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

    // Send the work to the apprentices
    for (int i{1}; i < worldsize + 1; ++i) {
        messenger.sendWork(i, work.getWork());
    }

    for (int i{}; i < worldsize; ++i) {
        std::vector<std::string> results = messenger.receiveResults();
        for (const auto& result : results) {
            std::cout << result << std::endl;
        }
    }
}

void Master::readWordlist()
{
    
}