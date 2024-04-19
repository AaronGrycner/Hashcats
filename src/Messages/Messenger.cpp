//
// Created by aaron on 4/16/24.
//

#include "Messenger.h"
#include "Logger.h"
#include "MessageFactory.h"

using namespace Messages;

Messenger::Messenger() {
    Logger::log("Initializing Messenger on rank: " + std::to_string(rank));
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

bool Messenger::check_for_message() {
    int flag;
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);

    if (flag != 0) {
        int size;
        std::string buffer;

        // get size of incoming data
        MPI_Get_count(&status, MPI_CHAR, &size);

        // resize buffer to incoming data size
        buffer.resize(size);

        MPI_Recv(buffer.data(), size, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        msg_buf = MessageFactory::parse_MPI_Status(status, buffer);

        return true;
    }

    return false;
}

std::shared_ptr<Messages::Message> Messenger::get_message() {
    std::shared_ptr<Messages::Message> temp = std::move(msg_buf);
    msg_buf = std::make_shared<Messages::Message>();
    return temp;
}

void Messenger::send_hello(int dest) {
    Logger::log("Sending 'Hello' message to destination: " + std::to_string(dest));
    MPI_Send(nullptr, 0, MPI_CHAR, dest, static_cast<int>(MessageType::HELLO), MPI_COMM_WORLD);
    Logger::log("Hello message sent to " + std::to_string(dest));
}

void Messenger::send_acknowledge(int dest) {
    Logger::log("Sending 'Acknowledge' message to destination: " + std::to_string(dest));
    MPI_Send(nullptr, 0, MPI_CHAR, dest, static_cast<int>(MessageType::ACKNOWLEDGE), MPI_COMM_WORLD);
    Logger::log("Acknowledge message sent to " + std::to_string(dest));
}

void Messenger::send_goodbye(int dest) {
    Logger::log("Sending 'Goodbye' message to destination: " + std::to_string(dest));
    MPI_Send(nullptr, 0, MPI_CHAR, dest, static_cast<int>(MessageType::GOODBYE), MPI_COMM_WORLD);
    Logger::log("Goodbye message sent to " + std::to_string(dest));
}

void Messenger::send_pcap(int dest, const FileData::PcapData &file) {
    Logger::log("Sending 'PCAP' data to destination: " + std::to_string(dest) + "; Data size: " + std::to_string(file.get_data().size()) + " bytes");
    MPI_Send(file.get_data().data(), static_cast<int>(file.get_data().size()), MPI_CHAR, dest, static_cast<int>(MessageType::PCAP), MPI_COMM_WORLD);
    Logger::log("PCAP data sent to " + std::to_string(dest));
}

void Messenger::send_wordlist(int dest, const FileData::WordlistData &file) {
    Logger::log("Sending 'Wordlist' data to destination: " + std::to_string(dest) + "; Data size: " + std::to_string(file.get_data().size()) + " bytes");
    MPI_Send(file.get_data().data(), static_cast<int>(file.get_data().size()), MPI_CHAR, dest, static_cast<int>(MessageType::WORDLIST), MPI_COMM_WORLD);
    Logger::log("Wordlist data sent to " + std::to_string(dest));
}

