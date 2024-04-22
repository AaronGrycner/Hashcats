#include "Node.h"

#include "Logger/Logger.h"
#include "Messages.h"
#include "utils.h"

using namespace Messages;

Node::Node() {
    // get mpi rank and world sizes
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Logger::log("Node rank: " + std::to_string(rank) + ", world size: " + std::to_string(worldsize) + ".");
}

void Node::handle_message() {
    auto type = static_cast<MessageType>(msg_buf->type());  // Get the message type.

    switch (type) {  // Switch on the message type.
        case MessageType::HELLO:  // If the message is a HELLO message.
            handle_hello();  // Handle the HELLO message.
            break;
        case MessageType::GOODBYE:  // If the message is a GOODBYE message.
            handle_goodbye();  // Set the done flag to true.
            break;
        case MessageType::WORDLIST:  // If the message is a WORDLIST message.
            handle_wordlist();  // Handle the WORDLIST message.
            break;
        case MessageType::HCCAPX:  // If the message is a HCCAPX message.
            handle_hccapx();  // Handle the HCCAPX message.
            break;
        case MessageType::SUCCESS:  // If the message is a SUCCESS message.
            handle_success();  // Handle the SUCCESS message.
            break;
        case MessageType::FAIL:  // If the message is a FAILURE message.
            handle_fail();  // Handle the FAILURE message.
            break;
        case MessageType::ACKNOWLEDGE:  // If the message is an ACKNOWLEDGE message.
            handle_acknowledge();  // Handle the ACKNOWLEDGE message.
            break;
        default:  // If the message is not recognized.
            Logger::log("Apprentice " + std::to_string(rank) + " received unknown message type.");
            break;
    }
}

Node::~Node() = default;
