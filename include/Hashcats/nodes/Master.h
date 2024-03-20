#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

#include <vector>

class Work;

class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticeList;
    std::vector<Work> workVec;

    void handleAcknowledge(const Message &msg) override;
    void handleHello(const Message &msg) override;
    void handleGoodbye(const Message &msg) override;

    void setBuffer(const std::string &str);

public:
    Master();
    ~Master() override;

    bool readWordlist(const std::string &list);

    bool sendWork(const std::vector<std::string> &work, const int &dest);

    void pingApprentices();
    void run() override;

};

#endif