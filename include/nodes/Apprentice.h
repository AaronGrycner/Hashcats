#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

#include "ApprenticeMessenger.h"

class Apprentice : public Node {
private:
    ApprenticeMessenger messenger;
    
public:
    Apprentice()=default;
    void run() override;
};

#endif