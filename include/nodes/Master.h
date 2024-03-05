#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "work.h"

class Master final : public Node {
private:
    Work work;
    Messenger messenger;
    void readWordlist();

public:
    Master();

    void run() override;
};

#endif