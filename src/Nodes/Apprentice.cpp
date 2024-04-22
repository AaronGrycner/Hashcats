#include "Apprentice.h"
#include "Messages.h"
#include "Logger.h" // Include the Logger class for logging messages.
#include "utils.h" // Include the utils namespace for utility functions such as sleep.

using namespace Messages;

Apprentice::Apprentice() {
}

// Destructor logs the exiting message, noting the rank of the Apprentice.
Apprentice::~Apprentice() {
    Logger::log("Apprentice " + std::to_string(rank) + " exiting...");
}

// Main running loop for the Apprentice.
void Apprentice::run() {
    while (!done) {  // Continue running until the done flag is set.
        Logger::log("Apprentice " + std::to_string(rank) + " running loop.");

        if (messenger.check_for_message()) {
            msg_buf = messenger.get_message();
            Logger::log("Received message of type: " + std::to_string(msg_buf->type()));
            handle_message();
        }

        if (recvd_wordlist && recvd_hccapx) {
            Logger::log("Received wordlist and hccapx, exiting...");
            break;
        }

        utils::sleep(500);  // Sleep for half a second to reduce CPU usage.
    }

    run_hashcat();
}

void Apprentice::handle_hello() {
    Logger::log("Received HELLO from master.");  // Logger the receipt of the HELLO message.
    Messenger::send_acknowledge(0);  // Send an ACKNOWLEDGE message to the master.
}

void Apprentice::handle_wordlist() {
    FileData::WordlistData wordlist;
    wordlist.set_data(msg_buf->get_data());

    Logger::log("Received wordlist from master.");

    wordlist.write_file(WORDLIST_FILE);

    recvd_wordlist = true;
}

void Apprentice::handle_hccapx() {
    FileData::HccapxData hccapx;
    hccapx.set_data(msg_buf->get_data());

    Logger::log("Received hccapx from master.");

    hccapx.write_file(HCCAPX_FILE);

    recvd_hccapx = true;
}

void Apprentice::handle_success() {
    // unused for apprentice
}

void Apprentice::handle_fail() {
    // unused for apprentice
}

void Apprentice::handle_acknowledge() {
    Logger::log("Received ACKNOWLEDGE from master.");
}

void Apprentice::handle_goodbye() {
    Logger::log("Received GOODBYE from master.");
    done = true;
}

void Apprentice::run_hashcat() {
    system(DELETE_POTFILE.c_str());
    Logger::log("Running hashcat...");

    if (system(HASHCAT_COMMAND.c_str()) == 0) {
        read_success_file();
        Messenger::send_success(0, correct_password);
    }
    else {
        Messenger::send_fail(0);
    }
}

void Apprentice::read_success_file() {
    std::ifstream file(SUCCESS_FILE);
    std::string line;

    if (file) {
        getline(file, line);
        size_t last_colon{line.rfind(':')};

        correct_password = line.substr(last_colon + 1);
    }
}
