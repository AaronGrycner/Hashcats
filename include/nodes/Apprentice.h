#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:

public:
    Apprentice()=default;
    ~Apprentice() override;
    void run() override;
};

#endif