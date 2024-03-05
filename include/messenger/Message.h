//
// Created by aaron on 3/1/24.
//

#ifndef MESSAGETAGS_H
#define MESSAGETAGS_H

#include <vector>
#include <string>

enum class MessageTag {
    HELLO, // sent by the master to apprentices to see if they are online
    GOODBYE, // sent by the master to apprentices to tell them to go offline
    ACKNOWLEDGE, // acknowledges hello from apprentice to master
    WORK_PAYLOAD, // sent by the master to apprentices to give them work
    WORK_RESULT, // sent by apprentices to the master to give them the result of their work
    RESULT_FOUND, // sent by the master to apprentices to tell them to stop working
};

class Message {
private:
    MessageTag tag;
    int dest_rank;
    bool bool_message{};

    std::vector<std::string> vec_message;

public:
    Message(const MessageTag &tag, const int &dest_rank) : tag(tag), dest_rank(dest_rank) {}
    Message(const MessageTag &tag, const int &dest_rank, std::vector<std::string> message) : tag(tag), dest_rank(dest_rank), vec_message(std::move(message)) {}
    Message(const MessageTag &tag, const int &dest_rank, const bool &message) : tag(tag), dest_rank(dest_rank), bool_message(message) {}

    int getRank() const { return dest_rank; }
    [[nodiscard]] MessageTag getTag() const { return tag; }
    [[nodiscard]] std::vector<std::string> getVecMessage() const { return vec_message; }
};

#endif //MESSAGETAGS_H
