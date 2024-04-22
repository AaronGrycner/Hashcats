#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

#include <vector>

class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticeList;

    void setup_apprentice_list();
    void listen();

    void handle_hello() override;
    void handle_wordlist() override;
    void handle_hccapx() override;
    void handle_success() override;
    void handle_fail() override;
    void handle_acknowledge() override;
    void handle_goodbye() override;

public:
    Master();
    ~Master() override;

    void pingApprentices();
    void distribute_files(const FileData::WordlistData &wordlist, const FileData::HccapxData &hccapx) const;
    void run() override;

};

#endif