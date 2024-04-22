#include "Master.h"

#include "Messages.h"
#include "Logger.h"
#include "utils.h"
#include "FileData/FileData.h"


// Constructor: initializes the apprentice list and reads the word list from a predefined constant file path.
Master::Master() {
    setup_apprentice_list();
    Logger::log("Master node initialized.");
}

// Destructor: logs when the Master is exiting.
Master::~Master() {
    Logger::log("Master exiting...");
}

void Master::setup_apprentice_list() {
    apprenticeList.resize(worldsize - 1);  // Resize apprentice list to match the number of non-master processes.

    // Assign ranks to each apprentice, starting from 1 (0 is typically the master).
    for (int i{1}; i < worldsize; ++i) {
        Logger::log("Adding apprentice with rank " + std::to_string(i));
        apprenticeList.at(i - 1).rank = i;  // Corrected indexing for zero-based vector
    }
}

// Sends a hello message to all apprentices except the master (rank 0).
void Master::pingApprentices() {
    for (ApprenticeInfo apprentice : apprenticeList) {
        Messenger::send_hello(apprentice.rank);
    }
}

// Main running loop for the Master.
void Master::run() {
    FileData::WordlistData wordlist;
    FileData::HccapxData hccapx;

    pingApprentices();  // Send a hello message to all apprentices.

    while(!done) {
        Logger::log("Master running loop.");

        if (messenger.check_for_message()) {
            msg_buf = messenger.get_message();

            // Check if the message is an ACKNOWLEDGE.
            if (msg_buf->type() == Messages::MessageType::ACKNOWLEDGE) {
                Logger::log("Received ACKNOWLEDGE from apprentice " + std::to_string(msg_buf->source()));
                done = true;
            }

        }
        utils::sleep(500);  // Sleep for half a second to reduce CPU usage.
    }

    wordlist.read_file(WORDLIST_FILE);  // Read the word list from the file.
    hccapx.read_file(HCCAPX_FILE);  // Read the hccapx file from the file.
    distribute_files(wordlist, hccapx);  // Distribute the word list to all apprentices.

    listen();  // Listen for messages from apprentices.
}

void Master::listen() {
    done = false;

    while (!done) {

        if (messenger.check_for_message()) {
            msg_buf = messenger.get_message();

            handle_message();
        }
        utils::sleep(500);
    }
}

void Master::distribute_files(const FileData::WordlistData &wordlist, const FileData::HccapxData &hccapx) const {
    int counter{};
    std::vector<FileData::WordlistData> wordlists{ wordlist.split(static_cast<int>(apprenticeList.size()))};

    for (ApprenticeInfo apprentice : apprenticeList) {
        Messenger::send_wordlist(apprentice.rank, wordlists.at(counter));
        utils::sleep(500);
        Messenger::send_hccapx(apprentice.rank, hccapx);
        ++counter;
    }
}

void Master::handle_hello() {
    Logger::log("Received HELLO from apprentice " + std::to_string(msg_buf->source()));
    Messenger::send_acknowledge(msg_buf->source());
}

void Master::handle_wordlist() {
    // unused for master
}

void Master::handle_hccapx() {
    // unused for master
}

void Master::handle_success() {
    Logger::log("Received SUCCESS from apprentice " + std::to_string(msg_buf->source()) + " with password: " + msg_buf->get_data());
    correct_password = msg_buf->get_data();
    done = true;
}

void Master::handle_fail() {
    Logger::log("Received FAIL from apprentice " + std::to_string(msg_buf->source()));
}

void Master::handle_acknowledge() {
    Logger::log("Received ACKNOWLEDGE from apprentice " + std::to_string(msg_buf->source()));
}

void Master::handle_goodbye() {
    Logger::log("Received GOODBYE from apprentice " + std::to_string(msg_buf->source()));
}