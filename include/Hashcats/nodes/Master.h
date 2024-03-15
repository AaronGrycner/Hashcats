#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

#include <vector>

class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticeList;

    void handleAcknowledge(const Message &msg) override;
    void handleHello(const Message &msg) override;
    void handleGoodbye(const Message &msg) override;

public:
    Master();
    ~Master()override=default;

    void pingApprentices();

    void run() override;

};

#endif