//
// Created by aaron on 3/7/24.
//

#include "Messenger.h"

Messenger::Messenger() {

}

void Messenger::listen() {
    MessageData temp{};

    while (!done) {
        MPI_Irecv(temp.buf, temp.count, temp.datatype, temp.source, temp.tag, MPI_COMM_WORLD, &temp.request);

        while (true) {
            if (MPI_Test(&temp.request, &temp.flag, &temp.status) || done) {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        queue.emplace(Message(temp));

    }
}

Message Messenger::getNextMessage() {
    const Message temp(queue.front());

    queue.pop();

    return temp;
}