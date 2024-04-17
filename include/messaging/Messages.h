#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <string>
#include <mpi.h>

#include "MessageTags.h"
#include "Work.h"
#include "defs.h"
#include "File/File.h"

namespace Messages {

    // Enum class defining types of messages that can be sent or received.
    enum class MessageType {
        HELLO,        // Sent by the master to apprentices to check if they are online.
        ACKNOWLEDGE,  // Sent in response to a HELLO, acknowledging receipt.
        GOODBYE,      // Indicates a connection or session is being closed.
        WORDLIST,         // Contains a list of words to be processed by an apprentice.
        PCAP          // Contains a pcap file for processing.
    };

    // Parent class representing an MPI message with encapsulation for MPI-specific details.
    class Message {
    protected:
        std::unique_ptr<char[]> _buf{std::make_unique<char[]>(BUFFER_SIZE)};   // Buffer for message data.
        int _count{};                   // Number of elements in the buffer.

        MPI_Datatype _datatype{MPI_CHAR}; // Type of data in the MPI message, default is char.
        int _dest{};                      // Destination rank in the MPI communicator.
        int _source{};                    // Source rank in the MPI communicator.
        int _tag{};                       // Tag to identify the message type.
        int _error{};                     // Error status of the message operation.

        inline void setBuffer(std::string &data) {
            _count = data.size();
            std::copy(data.begin(), data.end(), _buf.get());
        }

    public:
        Message() {
            MPI_Comm_rank(MPI_COMM_WORLD, &_source);
        }

        virtual void send() = 0;

        // Getters
        [[nodiscard]] char* buf() const { return _buf.get(); }
        [[nodiscard]] int count() const { return _count; }
        [[nodiscard]] MPI_Datatype datatype() const { return _datatype; }
        [[nodiscard]] int dest() const { return _dest; }
        [[nodiscard]] int source() const { return _source; }
        [[nodiscard]] int tag() const { return _tag; }
        [[nodiscard]] int error() const { return _error; }
    };


    //
    // HELLO
    //

    class HelloMessage : public Message {
    public:
        explicit HelloMessage(int dest);

        void send() override;

    };


    //
    // ACKNOWLEDGE
    //

    class AcknowledgeMessage : public Message {
    public:
        explicit AcknowledgeMessage(int dest);

        void send() override;

    };


    //
    // GOODBYE
    //

    class GoodbyeMessage : public Message {
    public:
        explicit GoodbyeMessage(int dest);

        void send() override;

    };


    //
    // PCAP
    //

    class PcapMessage : public Message {
    private:
        Files::PcapFile _file;

    public:
        PcapMessage(int dest, Files::PcapFile &file);

        void send() override;

        Files::PcapFile file() { return _file; }
    };


    //
    // WORDLIST
    //

    class WordlistMessage : public Message {
    private:
        Files::WordlistFile _file;

    public:
        WordlistMessage(int dest, Files::WordlistFile &file);

        void send() override;

        Files::WordlistFile file() { return _file; }
    };

}
#endif // MESSAGE_H
