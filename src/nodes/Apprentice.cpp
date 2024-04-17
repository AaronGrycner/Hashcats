#include "Apprentice.h"
#include "Messages.h"
#include "Logger.h" // Include the Logger class for logging messages.
#include "utils.h" // Include the utils namespace for utility functions such as sleep.

// Destructor logs the exiting message, noting the rank of the Apprentice.
Apprentice::~Apprentice() {
    Logger::log("Apprentice " + std::to_string(rank) + " exiting...");
}

// Handles acknowledge messages received from the Master.
void Apprentice::handleAcknowledge(const Message &msg) {
    Logger::log("Apprentice::handleAcknowledge - Acknowledgement received.");
}

// Handles goodbye messages from the Master and marks the apprentice as done.
void Apprentice::handleGoodbye(const Message &msg) {
    done = true;  // Set the done flag to true, indicating the apprentice should stop running.
    Logger::log("Apprentice::handleGoodbye - Marking as done.");
}

// Handles hello messages from the Master by sending back an acknowledgment.
void Apprentice::handleHello(const Message &msg) {
    sendMessage(Message(msg.source(), ACKNOWLEDGE));  // Send an acknowledge message back to the Master.
    Logger::log("Apprentice::handleHello - Responding with ACKNOWLEDGE.");
}

// Handles work messages from the Master by acknowledging receipt and storing the work.
void Apprentice::handleWork(const Message &msg) {
    sendMessage(Message(msg.source(), ACKNOWLEDGE));  // Respond with an acknowledgment to confirm receipt.
    Logger::log("Apprentice::handleWork - Responding with ACKNOWLEDGE.");
    work = msg.getWork();  // Store the work received in the message.

    done = true;  // Set the done flag to true to indicate the apprentice should stop running.
}

// Main running loop for the Apprentice.
void Apprentice::run() {
    while (!done) {  // Continue running until the done flag is set.
        if (messageCheck()) {  // Check for incoming messages.
            handle(msgBuf);  // Handle any messages that have been received.
        }
        utils::sleep(500);  // Sleep for half a second to reduce CPU usage.
    }

    writeWork();
}

void Apprentice::writeWork() {
    std::ofstream f("work.txt");

    if (f.is_open()) {
        for (const auto &word : work) {
            f << word << std::endl;
        }
        f.close();
    }

    else {
        Logger::log("Failed to open file for writing work.");
    }
}