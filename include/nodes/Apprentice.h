#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:
    Messenger messenger;
    
public:
    Apprentice()=default;
    void run() override;
};

#endif