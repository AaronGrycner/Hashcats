#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:
    void write_words();

public:
    Apprentice();
    ~Apprentice() override;

    void run() override;

};

#endif