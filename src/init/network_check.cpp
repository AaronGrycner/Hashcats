//
// Created by aaron on 4/11/24.
//

#include "../include/Hashcats/init/network_check.h"

#include "defs.h"

namespace init {

    std::string exec(const char* cmd) {
        std::array<char, 128> buffer{};
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

    std::string get_default_interface() {
        std::string result = exec("ip route | grep default | awk '{print $5}'");
        if (!result.empty()) {
            result.pop_back(); // Remove the newline character at the end of the string
        }
        return result;
    }

    // Retrieves the netmask for a specified network interface
    std::string get_netmask() {
        const std::string interface_name{get_default_interface()};
        struct ifaddrs* ifaddr, *ifa;
        char netmask[INET_ADDRSTRLEN];

        // Obtain the linked list of network interfaces
        if (getifaddrs(&ifaddr) == -1) {
            std::cerr << "Error getting interfaces" << std::endl;
            return "";
        }

        // Iterate over the list of interfaces
        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == nullptr)
                continue;

            // Check if it is an IPv4 address
            if (ifa->ifa_addr->sa_family == AF_INET) {
                // Compare the interface name
                if (std::strcmp(ifa->ifa_name, interface_name.c_str()) == 0) {
                    // Retrieve the netmask of the interface
                    void* tmpAddrPtr = &((struct sockaddr_in*) ifa->ifa_netmask)->sin_addr;
                    inet_ntop(AF_INET, tmpAddrPtr, netmask, INET_ADDRSTRLEN);
                    std::string result(netmask);
                    freeifaddrs(ifaddr);
                    return result; // Return the netmask as a string
                }
            }
        }

        freeifaddrs(ifaddr);
        return "";  // Return empty string if no netmask found
    }

    // Sends a ping to a specified IP address using the Tins library
    bool send_ping(const IPv4Address& address) {
        // Specify the network interface to use
        NetworkInterface iface(get_default_interface());
        NetworkInterface::Info info = iface.addresses();

        // Configure the packet sender to use the default interface
        PacketSender sender;
        sender.default_interface(iface);

        // Create an ICMP packet directed to the specified address
        IP pkt = IP(address, info.ip_addr) / ICMP();
        pkt.ttl(64); // Set the time-to-live for the packet

        // Send the packet and wait for a reply
        auto reply = sender.send_recv(pkt);
        if (reply) {
            return true; // Ping was successful
        } else {
            return false; // Ping failed
        }
    }

    // Pings a range of IP addresses in a subnet and returns the list of responsive hosts
    std::vector<std::string> ping_subnet(const std::string& cidr) {
        std::vector<std::string> responsiveIPs;

        // Parse CIDR to base IP and subnet mask
        size_t slashPos = cidr.find('/');
        if (slashPos == std::string::npos) {
            std::cerr << "Invalid CIDR format." << std::endl;
            return responsiveIPs;
        }

        std::string baseIP = cidr.substr(0, slashPos);
        int subnetMaskLength = std::stoi(cidr.substr(slashPos + 1));
        unsigned long mask = (0xFFFFFFFF << (32 - subnetMaskLength)) & 0xFFFFFFFF;
        IPv4Address networkAddress(baseIP);
        unsigned long networkAddressLong = networkAddress;

        // Calculate start and end addresses
        unsigned long startAddress = (networkAddressLong & mask) + 1; // +1 to exclude network address itself
        unsigned long endAddress = (startAddress | (~mask)) - 1; // -1 to exclude broadcast address

        // Ping the range
        for (unsigned long address = startAddress; address <= endAddress; ++address) {
            IPv4Address currentAddress(address);
            if (send_ping(currentAddress)) {
                responsiveIPs.emplace_back(currentAddress.to_string());
            }
        }

        return responsiveIPs;
    }

    bool network_check() {
        std::vector<std::string> network_list{ping_subnet(get_netmask())};

    }
}