#ifndef APPRENTICE_H
#define APPRENTICE_H

#include "Node.h"

class Apprentice : public Node {
private:
    bool recvd_hccapx{false}, recvd_wordlist{false};

    void run_hashcat();

    void handle_hello() override;
    void handle_wordlist() override;
    void handle_hccapx() override;
    void handle_success() override;
    void handle_fail() override;
    void handle_acknowledge() override;
    void handle_goodbye() override;

    void read_success_file();

public:
    Apprentice();
    ~Apprentice() override;

    void run() override;

};

#endif