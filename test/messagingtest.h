//
// Created by aaron on 3/1/24.
//

#include "Master.h"
#include "Apprentice.h"

inline void messageTest() {
    // Test the Hello message
    Node* node;
    MPI_Init(nullptr, nullptr);

    if(MPI_Comm_rank(MPI_COMM_WORLD, nullptr) > 0) {
        node = new Apprentice();
    }
    else {
        node = new Master();
    }

    node->run();

    delete node;
}
