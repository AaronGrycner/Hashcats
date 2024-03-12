#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticelist;

    void handleAcknowledge(const Message &msg) override;
    void handleHello(const Message &msg) override;
    void handleGoodbye(const Message &msg) override;

    void checkApprentices();

public:
    Master()=default;
    ~Master()override=default;

    void run() override;

};

#endif