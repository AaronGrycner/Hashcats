#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:
    static void write_words(const FileData::WordlistData &wordlist);

public:
    Apprentice();
    ~Apprentice() override;

    void run() override;

};

#endif