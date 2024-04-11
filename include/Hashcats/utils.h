//
// Created by aaron on 3/14/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <thread>

#include "defs.h"

namespace utils {

    inline void sleep(const int &ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}

#endif // UTILS_H
