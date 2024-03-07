#ifndef MASTER_H
#define MASTER_H

#include "Node.h"
#include "ApprenticeInfo.h"

class Master final : public Node {
private:
    void pingApprentices();
    std::vector<ApprenticeInfo> apprenticelist;

public:
    explicit Master()=default;
    ~Master() override;

    void run() override;

};

#endif