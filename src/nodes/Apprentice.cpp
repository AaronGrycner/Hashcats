#include "Apprentice.h"
#include "Messages.h"
#include "Logger.h" // Include the Logger class for logging messages.
#include "utils.h" // Include the utils namespace for utility functions such as sleep.

using namespace Messages;

// Destructor logs the exiting message, noting the rank of the Apprentice.
Apprentice::~Apprentice() {
    Logger::log("Apprentice " + std::to_string(rank) + " exiting...");
}

// Main running loop for the Apprentice.
void Apprentice::run() {
    Logger::log("Apprentice " + std::to_string(rank) + " starting main loop.");
    while (!done) {  // Continue running until the done flag is set.

        Logger::log("Apprentice " + std::to_string(rank) + " checking for messages.");  // Log the check for messages.
        if (messenger.check_for_message()) {  // Check for incoming messages.
            Logger::log("Apprentice " + std::to_string(rank) + " received message!!!!.");
            msg_buf = messenger.get_message();  // Get the message buffer.

            if (msg_buf->type() == MessageType::HELLO) {  // Check if the message is a HELLO message.
                Logger::log("Received HELLO from master.");  // Log the receipt of the HELLO message.
                messenger.send_acknowledge(0);  // Send an ACKNOWLEDGE message to the master.
                done = true;
            }
        }
        utils::sleep(500);  // Sleep for half a second to reduce CPU usage.
    }

    done = false;

    while (!done) {
        if (messenger.check_for_message()) {
            msg_buf = messenger.get_message();

            if (msg_buf->type() == MessageType::WORDLIST) {
                std::shared_ptr<WordlistMessage> wordlist_msg = std::dynamic_pointer_cast<WordlistMessage>(msg_buf);
                Logger::log("Received word list from master.");

                wordlist = wordlist_msg->get_file_data();
                done = true;
            }
        }
        utils::sleep(500);
    }

    write_words();
}

void Apprentice::write_words() {
    std::ofstream f("work.txt");

    if (f.is_open()) {
        f.write(wordlist.get_data().c_str(), static_cast<int>(wordlist.get_data().size()));
        f.close();

        Logger::log("Successfully wrote work to file.");
    }

    else {
        Logger::log("Failed to open file for writing work.");
    }
}