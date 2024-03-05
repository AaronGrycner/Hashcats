#include "Master.h"

#include "defs.h"

#include <stdexcept>
#include <iostream>
#include <utility>

Master::Master(const std::string &listname) : work((listname))
{
}

void Master::run()
{
    work.split(worldsize); // Split the work into the number of apprentices


}

void Master::sendHello(const int &dest)
{
    const messages::Hello hello(dest);
    MPI_Send(hello.buf(), hello.count(), hello.datatype(), hello.dest(), hello.tag(), MPI_COMM_WORLD);
}