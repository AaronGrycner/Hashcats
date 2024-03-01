#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "MasterMessenger.h"
#include "work.h"

class Master : public Node {
private:
    Work work;
    MasterMessenger messenger;
    void readWordlist();

public:
    Master();

    void run() override;
};

#endif