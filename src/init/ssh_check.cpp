//
// Created by aaron on 4/11/24.
//

#include "../include/Hashcats/init/ssh_check.h"

#include <filesystem>
#include <vector>

#include "defs.h"

namespace fs = std::filesystem;

namespace init {

    bool ssh_connect_test(const std::string& ip, const std::string& ssh_key) {
        std::string command = "ssh -i " + ssh_key + " " + SSH_USER + "@" + ip + " 'echo SSH_SUCCESS'";
        int returnCode = system(command.c_str());

        return (returnCode == 0); // Zero indicates success
    }

    bool update_key(const std::string& ip) {
        std::string cmd;

        cmd = "ssh -i " + SSH_INIT_KEY_PRIVATE + " " + SSH_USER + "@" + ip + " 'mkdir -p " + SSH_FINAL_KEYS_DIR + "'";
        if (system(cmd.c_str()) != 0){
            return false;
        }

        cmd = "scp -i " + SSH_INIT_KEY_PRIVATE + " " + SSH_FINAL_KEY_PUBLIC + " " + SSH_USER + "@" + ip + ":" + SSH_FINAL_KEYS_DIR;
        if (system(cmd.c_str()) != 0){
            return false;
        }

        cmd = "ssh -i " + SSH_FINAL_KEY_PRIVATE + " " + SSH_USER + "@" + ip + " 'mkdir -p " + SSH_FINAL_KEYS_DIR + "'";
        if (system(cmd.c_str()) != 0){
            return false;
        }

        return true;
    }

    // Function to create final SSH keys
    bool make_final_keys() {
        // Command to generate an SSH key pair
        std::string cmd{"ssh-keygen -t rsa -b 4096 -f " + SSH_FINAL_KEY_PRIVATE};
        // Execute command and capture the return value
        int result = system(cmd.c_str());
        // Return true if command execution was successful
        return result == 0;
    }

// Function to check if initial SSH keys are properly set up
    bool check_init_keys() {
        // Check if the directory exists and is indeed a directory
        if (!fs::exists(SSH_INIT_KEYS_DIR) || !fs::is_directory(SSH_INIT_KEYS_DIR)) {
            return false; // Return false if initial keys directory does not exist
        }

        // Check if both public and private keys exist
        if (!fs::exists(SSH_INIT_KEY_PUBLIC) || !fs::exists(SSH_INIT_KEY_PRIVATE)) {
            return false; // Return false if either key does not exist
        }

        return true; // Return true if all checks pass
    }

// Function to check if final SSH keys are properly set up
    bool check_final_keys() {
        // Check if the directory exists and is indeed a directory
        if (!fs::exists(SSH_FINAL_KEYS_DIR) || !fs::is_directory(SSH_FINAL_KEYS_DIR)) {
            return false;
        }

        // Check if both public and private keys exist
        if (!fs::exists(SSH_FINAL_KEY_PUBLIC) || !fs::exists(SSH_FINAL_KEY_PRIVATE)) {
            if (!make_final_keys()) { // Attempt to create keys if they don't exist
                return false;
            }
        }

        return true; // Return true if all checks pass
    }

// Function to perform overall SSH checks
    void ssh_check() {
        std::vector<std::string> network;

        if (!check_init_keys()) { // Check initial keys
            throw std::runtime_error("Initial SSH keys check failed"); // Throw if check fails
        }
        if (!check_final_keys()) { // Check final keys
            throw std::runtime_error("Final SSH keys check failed"); // Throw if check fails
        }

        // check all machines for init keys
        for (const std::string &ip : network) {
            if (ssh_connect_test(ip, SSH_INIT_KEY_PUBLIC)) {
                update_key(ip);
            }
        }
    }
}