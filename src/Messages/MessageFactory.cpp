//
// Created by aaron on 4/17/24.
//

#include "Messages/MessageFactory.h"
#include "Logger.h"

#include <utility>

namespace Messages {
    std::shared_ptr<Messages::Message> MessageFactory::parse_MPI_Status(const MPI_Status &status, const std::string &buffer) {
        int count, source{status.MPI_SOURCE}, tag{status.MPI_TAG};

        MPI_Get_count(&status, MPI_CHAR, &count);

        std::shared_ptr<Message> msg;

        switch (tag) {
            case HELLO:
                msg = std::make_shared<HelloMessage>(MessageFactory::create_hello(buffer, count, MPI_CHAR, source, tag, MPI_COMM_WORLD));
                return msg;

            case ACKNOWLEDGE:
                msg = std::make_shared<AcknowledgeMessage>(MessageFactory::create_acknowledge(buffer, count, MPI_CHAR, source, tag, MPI_COMM_WORLD));
                return msg;

            case GOODBYE:
                msg = std::make_shared<GoodbyeMessage>(MessageFactory::create_goodbye(buffer, count, MPI_CHAR, source, tag, MPI_COMM_WORLD));
                return msg;

            case PCAP:
                msg = std::make_shared<PcapMessage>(MessageFactory::create_pcap(buffer, count, MPI_CHAR, source, tag, MPI_COMM_WORLD));
                return msg;

            case WORDLIST:
                msg = std::make_shared<WordlistMessage>(MessageFactory::create_wordlist(buffer, count, MPI_CHAR, source, tag, MPI_COMM_WORLD));
                return msg;

            default:
                Logger::log("Unrecognized message tag");
                throw std::runtime_error("Unrecognized message tag");
        }

    }

    void set_data(Message &msg, const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
        msg.set_buf(buf);
        msg.set_count(count);
        msg.set_datatype(datatype);
        msg.set_dest(dest);
        msg.set_tag(tag);
    }

    HelloMessage MessageFactory::create_hello(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
        HelloMessage msg;
        set_data(msg, buf, count, datatype, dest, tag, comm);
        return msg;
    }

    AcknowledgeMessage MessageFactory::create_acknowledge(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
        AcknowledgeMessage msg;
        set_data(msg, buf, count, datatype, dest, tag, comm);
        return msg;
    }

    GoodbyeMessage MessageFactory::create_goodbye(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
        GoodbyeMessage msg;
        set_data(msg, buf, count, datatype, dest, tag, comm);
        return msg;
    }

    PcapMessage MessageFactory::create_pcap(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
        PcapMessage msg;
        set_data(msg, buf, count, datatype, dest, tag, comm);
        return msg;
    }

    WordlistMessage MessageFactory::create_wordlist(const std::string &buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
        WordlistMessage msg;
        set_data(msg, buf, count, datatype, dest, tag, comm);
        return msg;
    }
} // Messages