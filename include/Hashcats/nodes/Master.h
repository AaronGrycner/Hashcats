#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

#include <vector>

#include "Work.h"

class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticeList;
    std::vector<Work> workVec;

    void handleAcknowledge(const Message &msg) override;
    void handleHello(const Message &msg) override;
    void handleGoodbye(const Message &msg) override;
    void handleWork(const Message &msg) override;

public:
    Master();
    ~Master() override;

    void pingApprentices();
    void run() override;

};

#endif