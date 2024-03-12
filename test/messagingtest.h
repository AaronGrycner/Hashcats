//
// Created by aaron on 3/1/24.
//

#include "Master.h"
#include "Apprentice.h"

inline void messageTest() {
    // Test the Hello message

    if(MPI_Comm_rank(MPI_COMM_WORLD, nullptr) > 0) {
        Apprentice node;
        node.send(Message(0, HELLO));

        if (node.listen()) {
            std::cout << "Response heard from Master. Success.";
        }
        else {
            std::cout << "No response heard. Fail.";
        }
    }
    else {
        Master node;
        node.pingApprentices();

        if (node.listen()) {
            std::cout << "Response heard from at least one Apprentice. Success.";
        }
        else {
            std::cout << "No responses heard. Fail.";
        }
    }
}
