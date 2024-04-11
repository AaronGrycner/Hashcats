#ifndef HASHCATS_NETWORK_CHECK_H
#define HASHCATS_NETWORK_CHECK_H

#include <libssh/libssh.h>
#include <vector>
#include <string>
#include <tins/tins.h>
#include <iostream>
#include <functional>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

// Using the Tins namespace for convenience
using namespace Tins;

namespace init {
    std::string exec(const char* cmd);
    std::string get_default_interface();
    std::string get_netmask();
    bool send_ping(const IPv4Address& address);
    std::vector<std::string> ping_subnet(const std::string& cidr);
    bool network_check();
}

#endif //HASHCATS_NETWORK_CHECK_H
