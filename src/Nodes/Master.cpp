#include "Master.h"

#include "Messages.h"
#include "Logger.h"
#include "utils.h"
#include "FileData/FileData.h"


// Constructor: initializes the apprentice list and reads the word list from a predefined constant file path.
Master::Master() {
    apprenticeList.resize(worldsize - 1);  // Resize apprentice list to match the number of non-master processes.

    // Assign ranks to each apprentice, starting from 1 (0 is typically the master).
    for (int i{1}; i < worldsize; ++i) {
        Logger::log("Adding apprentice with rank " + std::to_string(i));
        apprenticeList.at(i - 1).rank = i;  // Corrected indexing for zero-based vector
    }
}

// Destructor: logs when the Master is exiting.
Master::~Master() {
    Logger::log("Master exiting...");
}

// Sends a hello message to all apprentices except the master (rank 0).
void Master::pingApprentices() {
    for (ApprenticeInfo apprentice : apprenticeList) {
        messenger.send_hello(apprentice.rank);
    }
}

// Main running loop for the Master.
void Master::run() {
    FileData::WordlistData wordlist;

    pingApprentices();

    while(!done) {
        if (messenger.check_for_message()) {
            msg_buf = messenger.get_message();

            // Check if the message is an ACKNOWLEDGE.
            if (msg_buf->type() == Messages::MessageType::ACKNOWLEDGE) {
                Logger::log("Received ACKNOWLEDGE from apprentice " + std::to_string(msg_buf->source()));
                done = true;  // Set the done flag to true to exit the loop.
            }

        }
        utils::sleep(500);  // Sleep for half a second to reduce CPU usage.
    }

    wordlist.read_file(WORDLIST_FILE);  // Read the word list from the file.
    distribute_wordlist(wordlist);  // Distribute the word list to all apprentices.
}

void Master::distribute_wordlist(const FileData::WordlistData &wordlist) const {
    int counter{};
    std::vector<FileData::WordlistData> list{ wordlist.split(static_cast<int>(apprenticeList.size())) };

    for (ApprenticeInfo apprentice : apprenticeList) {
        Messenger::send_wordlist(apprentice.rank, list.at(counter));
        ++counter;
    }
}