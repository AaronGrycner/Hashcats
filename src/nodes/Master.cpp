#include "Master.h"

Master::Master(const std::string &listname) : work((listname))
{
    listen();
}

void Master::run()
{

    work.split(worldsize); // Split the work into the number of apprentices

}

void Master::findApprentices() {
    apprenticelist.resize(worldsize);
    int i{1};

    for (ApprenticeInfo apprentice : apprenticelist) {
        sendHello(i);
        ++i;
    }
}