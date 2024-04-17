#include "Master.h"
#include "Apprentice.h"

#include "Messages.h"
#include "Logger.h"
#include "utils.h"

// Constructor: initializes the apprentice list and reads the word list from a predefined constant file path.
Master::Master() {
    apprenticeList.resize(worldsize);  // Resize apprentice list to match the number of processes.

    // Assign ranks to each apprentice, starting from 1 (0 is typically the master).
    for (int i{1}; i < worldsize; ++i) {
        Logger::log("Adding apprentice with rank " + std::to_string(i));
        apprenticeList.at(i).rank = i;
    }

    readWordlist(WORDLIST);  // Read the list of words from a file specified by the WORDLIST constant.
}

// Destructor: logs when the Master is exiting.
Master::~Master() {
    Logger::log("Master exiting...");
}

// Sends a hello message to all apprentices except the master (rank 0).
void Master::pingApprentices() {
    for (ApprenticeInfo apprentice : apprenticeList) {
        if (apprentice.rank != 0) {  // Check to ensure the master does not ping itself.
            sendMessage(Message(apprentice.rank, HELLO));
        }
    }
}

// Handles acknowledge messages received from apprentices.
void Master::handleAcknowledge(const Message &msg) {
    Logger::log("Master::handleAcknowledge - Acknowledgement received from " + std::to_string(msg.source()));
    apprenticeList.at(msg.source()).active = true;  // Mark the apprentice as active upon receiving acknowledgment.
}

// Handles hello messages received from apprentices, and sends an acknowledgement back.
void Master::handleHello(const Message &msg) {
    apprenticeList.at(msg.source()).active = true;  // Mark the apprentice as active.
    Logger::log("Master::handleHello - Hello received from " + std::to_string(msg.source()));
    sendMessage(Message(msg.source(), ACKNOWLEDGE));  // Send an acknowledgement message back to the apprentice.
}

// Handles goodbye messages from apprentices, marking them as inactive.
void Master::handleGoodbye(const Message &msg) {
    apprenticeList.at(msg.source()).active = false;
    Logger::log("Master::handleGoodbye - Goodbye received from " + std::to_string(msg.source()));
}

// Main running loop for the Master.
void Master::run() {
    pingApprentices();  // Start by pinging all apprentices.

    while(!done) {  // Continue until the done flag is set to true.
        if (messageCheck()) {  // Check for incoming messages.
            handle(msgBuf);  // Handle any received messages.
            done = true;  // Optionally set done to true to exit loop after handling a message.
        }

        utils::sleep(500);  // Sleep for half a second to reduce CPU usage.
    }

    splitWork();  // Split work among active apprentices.
    sendWork();  // Send out the work to each apprentice.
}

// Handles work-related messages (not currently implemented as needed).
void Master::handleWork(const Message &msg) {
    // Placeholder function for potential future use.
}

// Splits the word list into roughly equal parts for each apprentice.
void Master::splitWork() {
    int i{}, appNum{worldsize-1};  // Calculate the number of apprentices (excluding the master).

    workVec.resize(worldsize - 1);  // Resize work vector to hold tasks for each apprentice.

    // Distribute words round-robin to the apprentices' work lists.
    for (const std::string &word : wordlist) {
        workVec.at(i % appNum).emplace_back(word);
        ++i;
    }
}

// Sends the allocated work to each apprentice.
void Master::sendWork() {
    for (const ApprenticeInfo &apprentice : apprenticeList) {
        if (apprentice.rank != 0) {  // Skip the master itself (rank 0).
            Logger::log("Sending work to apprentice " + std::to_string(apprentice.rank));
            sendMessage(Message(apprentice.rank, WORK, workVec.at(apprentice.rank - 1)));
        }
    }
}

// Reads a list of words from a file and stores them in the wordlist vector.
void Master::readWordlist(const std::string &listname) {
    std::string temp;
    std::ifstream f(listname);  // Open the file.

    while(f.good()) {  // Read until the end of the file.
        getline(f, temp);  // Read each line into temp.
        wordlist.emplace_back(temp);  // Add the word to the list.
    }
}

void Master::resultListen() {
    // Placeholder function for potential future use.
}
