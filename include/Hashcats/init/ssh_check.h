//
// Created by aaron on 4/11/24.
//

#ifndef HASHCATS_SSH_CHECK_H
#define HASHCATS_SSH_CHECK_H

#include <string>

namespace init {
    bool ssh_connect_test(const std::string& ip, const std::string& ssh_key);
    bool make_final_keys();
    bool check_init_keys();
    bool check_final_keys();
    void ssh_check();
}

#endif //HASHCATS_SSH_CHECK_H
