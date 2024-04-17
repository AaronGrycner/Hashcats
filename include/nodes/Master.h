#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"
#include "Work.h"

#include <vector>


class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticeList;
    std::vector<Work> workVec;
    std::vector<std::string> wordlist;

    void handleAcknowledge(const Messages::AcknowledgeMessage &msg) override;
    void handleHello(const Messages::HelloMessage &msg) override;
    void handleGoodbye(const Messages::GoodbyeMessage &msg) override;
    void handleWordlist(const Messages::WordlistMessage &msg) override;
    void handlePcap(const Messages::PcapMessage &msg) override;

    void splitWork();
    void sendWork();
    void readWordlist(const std::string &listname);

    void resultListen();

public:
    Master();
    ~Master() override;

    void pingApprentices();
    void run() override;

};

#endif