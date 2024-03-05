#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "Work.h"
#include "ApprenticeInfo.h"

#include <queue>
#include <mutex>

using namespace messages;

class Master final : public Node {
private:
    Work work;
    static void sendHello(const int &dest);

    void findApprentices();

    std::vector<ApprenticeInfo> apprenticelist;

public:
    explicit Master(const std::string &listname);
    ~Master() override;
    void run() override;

};

#endif