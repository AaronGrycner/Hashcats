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
                msg = std::make_shared<HelloMessage>(HelloMessage(status.MPI_SOURCE));
                return msg;

            case ACKNOWLEDGE:
                msg = std::make_shared<AcknowledgeMessage>(AcknowledgeMessage(status.MPI_SOURCE));
                return msg;

            case GOODBYE:
                msg = std::make_shared<GoodbyeMessage>(GoodbyeMessage(status.MPI_SOURCE));
                return msg;

            case PCAP:
                msg = std::make_shared<PcapMessage>(PcapMessage(status.MPI_SOURCE, buffer));
                return msg;

            case WORDLIST:
                msg = std::make_shared<WordlistMessage>(WordlistMessage(status.MPI_SOURCE, buffer));
                return msg;

            default:
                Logger::log("Unrecognized message tag");
                throw std::runtime_error("Unrecognized message tag");
        }

    }
} // Messages