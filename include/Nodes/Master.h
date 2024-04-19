#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

#include <vector>

class Master final : public Node {
private:
    std::vector<ApprenticeInfo> apprenticeList;

public:
    Master();
    ~Master() override;

    void pingApprentices();
    void distribute_wordlist(const FileData::WordlistData &wordlist) const;
    void run() override;

};

#endif