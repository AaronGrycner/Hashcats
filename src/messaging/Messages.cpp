//
// Created by aaron on 4/16/24.
//

#include <cstring>
#include "Messages.h"

namespace Messages {

    //
    // HELLO
    //

    HelloMessage::HelloMessage(int dest) {
        _dest = dest;
        _tag = static_cast<int>(MessageType::HELLO);
    }

    void HelloMessage::send() {
        MPI_Send(_buf.get(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
    }


    //
    // ACKNOWLEDGE
    //

    AcknowledgeMessage::AcknowledgeMessage(int dest) {
        _dest = dest;
        _tag = static_cast<int>(MessageType::ACKNOWLEDGE);
    }

    void AcknowledgeMessage::send() {
        MPI_Send(_buf.get(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
    }


    //
    // GOODBYE
    //

    GoodbyeMessage::GoodbyeMessage(int dest) {
        _dest = dest;
        _tag = static_cast<int>(MessageType::GOODBYE);
    }

    void GoodbyeMessage::send() {
        MPI_Send(_buf.get(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
    }


    //
    // PCAP
    //

    PcapMessage::PcapMessage(int dest, Files::PcapFile &file) : _file(file) {
        _dest = dest;
        _tag = static_cast<int>(MessageType::PCAP);

        auto size = _file.get_serialized_size();
        _buf = std::make_unique<char[]>(size);

        std::memcpy(_buf.get(), _file.get_serialized(), size);
        _count = static_cast<int>(size);
    }

    void PcapMessage::send() {
        MPI_Send(_buf.get(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
    }

    //
    // WORDLIST
    //

    WordlistMessage::WordlistMessage(int dest, Files::WordlistFile &file) : _file(file) {
        _dest = dest;
        _tag = static_cast<int>(MessageType::WORDLIST);

        auto size = _file.get_serialized_size();
        _buf = std::make_unique<char[]>(size);

        std::memcpy(_buf.get(), _file.get_serialized(), size);
        _count = static_cast<int>(size);
    }

    void WordlistMessage::send() {
        MPI_Send(_buf.get(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
    }
}