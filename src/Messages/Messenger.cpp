//
// Created by aaron on 4/16/24.
//

#include "Messenger.h"
#include "Logger.h"
#include "MessageFactory.h"

using namespace Messages;

Messenger::Messenger() {
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    reset_buffer();

    if (startListen()) {
        Logger::log(std::to_string(rank) + " successfully started Irecv.");
    } else {
        Logger::log(std::to_string(rank) + " failed starting Irecv.");
    }
}

void Messenger::reset_buffer() {
    buffer.clear();
    buffer.resize(BUFFER_SIZE);
}

bool Messenger::check_for_message() {
    int flag, ret{MPI_Test(&request, &flag, &status)};
    Logger::log(std::to_string(rank) + " checking for messages");

    if ((ret == MPI_SUCCESS) && flag) {
        Logger::log(std::to_string(rank) + " successfully received message from " + std::to_string(msg_buf->source()) + " and adding to queue");

        msg_buf = MessageFactory::parse_MPI_Status(status, buffer);

        reset_buffer();
        startListen(); // restart async listen on successful message receive

        return true;

    } else if ((ret == MPI_SUCCESS) && !flag) {
        Logger::log(std::to_string(rank) + " succesfully checked messages but none found");
        return false;
    } else {
        Logger::log(std::to_string(rank) + " message check fail");
        return false;
    }
}

bool Messenger::startListen() {
    int ret{MPI_Irecv(buffer.data(), BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &request) ==
            MPI_SUCCESS};

    if (ret) {
        Logger::log(std::to_string(rank) + " successfully started async receive.");
    } else {
        Logger::log(std::to_string(rank) + std::to_string(rank) + " failed to start async receive");
    }

    return ret;
}

void Messenger::send_hello(int dest) {
    Logger::log("Sending 'Hello' message to destination: " + std::to_string(dest));
    MessageFactory::create_hello("", 0, MPI_CHAR, dest, static_cast<int>(MessageType::HELLO), MPI_COMM_WORLD).send();
    Logger::log("Hello message sent to " + std::to_string(dest));
}

void Messenger::send_acknowledge(int dest) {
    Logger::log("Sending 'Acknowledge' message to destination: " + std::to_string(dest));
    MessageFactory::create_acknowledge("", 0, MPI_CHAR, dest, static_cast<int>(MessageType::ACKNOWLEDGE), MPI_COMM_WORLD).send();
    Logger::log("Acknowledge message sent to " + std::to_string(dest));
}

void Messenger::send_goodbye(int dest) {
    Logger::log("Sending 'Goodbye' message to destination: " + std::to_string(dest));
    MessageFactory::create_goodbye("", 0, MPI_CHAR, dest, static_cast<int>(MessageType::GOODBYE), MPI_COMM_WORLD).send();
    Logger::log("Goodbye message sent to " + std::to_string(dest));
}

void Messenger::send_pcap(int dest, const FileData::PcapData &file) {
    Logger::log("Sending 'PCAP' data to destination: " + std::to_string(dest) + "; Data size: " + std::to_string(file.get_data().size()) + " bytes");
    MessageFactory::create_pcap(file.get_data(), static_cast<int>(file.get_data().size()), MPI_CHAR, dest, static_cast<int>(MessageType::PCAP), MPI_COMM_WORLD).send();
    Logger::log("PCAP data sent to " + std::to_string(dest));
}

void Messenger::send_wordlist(int dest, const FileData::WordlistData &file) {
    Logger::log("Sending 'Wordlist' data to destination: " + std::to_string(dest) + "; Data size: " + std::to_string(file.get_data().size()) + " bytes");
    MessageFactory::create_wordlist(file.get_data(), static_cast<int>(file.get_data().size()), MPI_CHAR, dest, static_cast<int>(MessageType::WORDLIST), MPI_COMM_WORLD).send();
    Logger::log("Wordlist data sent to " + std::to_string(dest));
}
