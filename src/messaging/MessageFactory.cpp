//
// Created by aaron on 4/16/24.
//

#include "MessageFactory.h"

namespace Messages {

    HelloMessage create_hello_message(int dest) {
        return HelloMessage(dest);
    }

    AcknowledgeMessage create_acknowledge_message(int dest) {
        return AcknowledgeMessage(dest);
    }

    GoodbyeMessage create_goodbye_message(int dest) {
        return GoodbyeMessage(dest);
    }

    PcapMessage create_pcap_message(int dest, PcapFile &file) {
        return PcapMessage(dest, file);
    }

    WordlistMessage create_wordlist_message(int dest, WordlistFile &file) {
        return WordlistMessage(dest, file);
    }

} // Messages