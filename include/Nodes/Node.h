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

    std::string correct_password{};

    MPI_Request request{};
    MPI_Status status{};

    std::shared_ptr<Messages::Message> msg_buf = std::make_shared<Messages::Message>();

    Messenger messenger;

    void handle_message();

    virtual void handle_hello()=0;
    virtual void handle_wordlist()=0;
    virtual void handle_hccapx()=0;
    virtual void handle_goodbye()=0;
    virtual void handle_success()=0;
    virtual void handle_fail()=0;
    virtual void handle_acknowledge()=0;

public:
    Node();
    virtual ~Node()=0;

    virtual void run()=0;

};

#endif