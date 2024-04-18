#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <string>
#include <mpi.h>

#include "defs.h"
#include "FileData/FileData.h"

namespace Messages {

    // Enum class defining types of messages that can be sent or received.
    enum MessageType {
        HELLO,        // Sent by the master to apprentices to check if they are online.
        ACKNOWLEDGE,  // Sent in response to a HELLO, acknowledging receipt.
        GOODBYE,      // Indicates a connection or session is being closed.
        WORDLIST,         // Contains a list of words to be processed by an apprentice.
        PCAP          // Contains a pcap file for processing.
    };

    // Parent class representing an MPI message with encapsulation for MPI-specific details.
    class Message {
    protected:
        std::string _buf;   // Buffer for message data.
        int _count{};                   // Number of elements in the buffer.

        MPI_Datatype _datatype{MPI_CHAR}; // Type of data in the MPI message, default is char.
        int _dest{};                      // Destination rank in the MPI communicator.
        int _source{};                    // Source rank in the MPI communicator.
        int _tag{};                       // Tag to identify the message type.
        int _error{};                     // Error status of the message operation.

    public:
        Message()=default;

        virtual void send();

        // Getters
        [[nodiscard]] std::string buf() const { return _buf; }
        [[nodiscard]] int count() const { return _count; }
        [[nodiscard]] MPI_Datatype datatype() const { return _datatype; }
        [[nodiscard]] int dest() const { return _dest; }
        [[nodiscard]] int source() const { return _source; }
        [[nodiscard]] int type() const { return _tag; }
        [[nodiscard]] int error() const { return _error; }

        // Setters
        void set_dest(int dest) { _dest = dest; }
        void set_tag(int tag) { _tag = tag; }
        void set_error(int error) { _error = error; }
        void set_source(int source) { _source = source; }
        void set_count(int count) { _count = count; }
        void set_datatype(MPI_Datatype datatype) { _datatype = datatype; }
        void set_buf(std::string buf) { _buf = std::move(buf); }
    };


    //
    // HELLO
    //

    class HelloMessage : public Message {
    public:
        HelloMessage()=default;

        void send() override {
            MPI_Send(_buf.c_str(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
        }
    };


    //
    // ACKNOWLEDGE
    //

    class AcknowledgeMessage : public Message {
    public:
        AcknowledgeMessage()=default;

        void send() override {
            MPI_Send(_buf.c_str(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
        }
    };


    //
    // GOODBYE
    //

    class GoodbyeMessage : public Message {
    public:
        GoodbyeMessage()=default;
        void send() override {
            MPI_Send(_buf.c_str(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
        }
    };


    //
    // PCAP
    //

    class PcapMessage : public Message {
    private:
        FileData::PcapData _file;

    public:
        PcapMessage()=default;

        void send() override {
            MPI_Send(_buf.c_str(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
        }

        FileData::PcapData get_file_data() {
            return _file;
        };
    };


    //
    // WORDLIST
    //

    class WordlistMessage : public Message {
    private:
        FileData::WordlistData _file;

    public:
        WordlistMessage()=default;

        void send() override {
            MPI_Send(_buf.c_str(), _count, _datatype, _dest, _tag, MPI_COMM_WORLD);
        }

        FileData::WordlistData get_file_data() {
            return _file;
        };
    };

    inline void Message::send() {
        // Do nothing
    }
}
#endif // MESSAGE_H
