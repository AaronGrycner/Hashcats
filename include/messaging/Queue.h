//
// Created by aaron on 3/11/24.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <queue>
#include "Message.h"

namespace messages {
    class MessageQueue {
    private:
        mutable std::mutex mtx;
        std::queue<Message> queue;

    public:
        MessageQueue()=default;
        Message front() const {
            std::lock_guard<std::mutex> lock(mtx);
            return queue.front();
        }

        void pop() {
            std::lock_guard<std::mutex> lock(mtx);
            queue.pop();
        }

        void emplace(const Message &msg) {
            std::lock_guard<std::mutex> lock(mtx);
            queue.emplace(msg);
        }
    };

}


#endif //QUEUE_H
