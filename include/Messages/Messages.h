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
        SUCCESS,      // Indicates a successful operation. The message buffer contains the found work
        FAIL,         // Indicates unsuccessful cracking attempt, buffer is empty
        WORDLIST,         // Contains a list of words to be processed by an apprentice.
        HCCAPX          // Contains a pcap file for processing.
    };

    // Parent class representing an MPI message with encapsulation for MPI-specific details.
    class Message {
    protected:
        std::string _data;
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
        std::string get_data() { return _data; }
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

    class HccapxMessage : public Message {
    public:
        HccapxMessage(int source, std::string buffer) {
            _tag = MessageType::HCCAPX;
            _source = source;
            _data = std::move(buffer);
        }



    };

    //
    // WORDLIST
    //

    class WordlistMessage : public Message {
    public:
        WordlistMessage(int source, std::string buffer) {
            _tag = MessageType::WORDLIST;
            _source = source;
            _data = std::move(buffer);
        }
    };

    //
    // SUCCESS
    //

    class SuccessMessage : public Message {
    public:
        SuccessMessage(int source, std::string buffer) {
            _tag = MessageType::SUCCESS;
            _source = source;
            _data = std::move(buffer);
        }
    };

    //
    // FAIL
    //

    class FailMessage : public Message {
    public:
        explicit FailMessage(int source) {
            _tag = MessageType::FAIL;
            _source = source;
        }
    };
}

#endif

