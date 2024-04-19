#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <string>
#include <mpi.h>

#include "defs.h"
#include "FileData/FileData.h"
#include "Logger/Logger.h"

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
        int _tag{};                         // MPI tag for the message.
        int _source{};                       // Source rank in the MPI communicator.

    public:
        Message() = default;
        virtual ~Message() = default;

        [[nodiscard]] int source() const { return _source; }
        [[nodiscard]] int type() const { return _tag; }

        // Setters
        void set_tag(int tag) { _tag = tag; }
        void set_source(int source) { _source = source; }
    };


    //
    // HELLO
    //

    class HelloMessage : public Message {
    public:
        explicit HelloMessage(int source) {
            _tag = MessageType::HELLO;
            _source = source;
        }
    };

    //
    // ACKNOWLEDGE
    //

    class AcknowledgeMessage : public Message {
    public:
        explicit AcknowledgeMessage(int source) {
            _tag = MessageType::ACKNOWLEDGE;
            _source = source;
        }
    };

    //
    // GOODBYE
    //

    class GoodbyeMessage : public Message {
    public:
        explicit GoodbyeMessage(int source) {
            _tag = MessageType::GOODBYE;
            _source = source;
        }
    };

    //
    // PCAP
    //

    class PcapMessage : public Message {
    private:
        FileData::PcapData _data;

    public:
        PcapMessage(int source, const std::string &data) {
            _tag = MessageType::PCAP;
            _source = source;
            _data.set_data(data);
        }

        FileData::PcapData get_file_data() {
            return _data;
        };

        void set_data(const FileData::PcapData &data) {
            _data = data;
        }
    };

    //
    // WORDLIST
    //

    class WordlistMessage : public Message {
    private:
        FileData::WordlistData _data;

    public:
        WordlistMessage(int source, const std::string &data) {
            _tag = MessageType::WORDLIST;
            _source = source;
            _data.set_data(data);
        }

        FileData::WordlistData get_file_data() {
            return _data;
        };

        void set_data(const FileData::WordlistData &data) {
            _data = data;
        }
    };
}

#endif

