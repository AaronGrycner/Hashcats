#ifndef NODE_H
#define NODE_H

#include <mpi.h>
#include <memory>

#include "defs.h"
#include "Messages.h"
#include "Messenger.h"

class Node {
protected:
    int rank{}, worldsize{};
    bool done{false};

    MPI_Request request{};
    MPI_Status status{};

    std::shared_ptr<Messages::Message> msg_buf = std::make_shared<Messages::Message>();

    Messenger messenger;

public:
    Node();
    virtual ~Node()=0;

    [[nodiscard]] int getRank() const { return rank; }
    [[nodiscard]] int getWorldSize() const { return worldsize; }

    virtual void run()=0;

};

#endif