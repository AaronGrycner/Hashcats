//
// Created by aaron on 4/16/24.
//

#ifndef HASHCATS_MESSAGEFACTORY_H
#define HASHCATS_MESSAGEFACTORY_H

#include "Messages.h"
#include "File/File.h"

using namespace Files;

namespace Messages {
    HelloMessage create_hello_message(int dest);
    AcknowledgeMessage create_acknowledge_message(int dest);
    GoodbyeMessage create_goodbye_message(int dest);
    PcapMessage create_pcap_message(int dest, PcapFile &file);
    WordlistMessage create_wordlist_message(int dest, WordlistFile &file);
} // Messages

#endif //HASHCATS_MESSAGEFACTORY_H
