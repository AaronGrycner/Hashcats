//
// Created by aaron on 3/1/24.
//

#ifndef MESSAGETAGS_H
#define MESSAGETAGS_H

enum MessageTag {
    HELLO, // sent by the master to apprentices to see if they are online
    GOODBYE, // sent by the master to apprentices to tell them to go offline
    ACKNOWLEDGE, // acknowledges hello from apprentice to master
    WORK_PAYLOAD, // sent by the master to apprentices to give them work
    WORK_RESULT, // sent by apprentices to the master to give them the result of their work
    RESULT_FOUND, // sent by the master to apprentices to tell them to stop working
};

#endif //MESSAGETAGS_H
