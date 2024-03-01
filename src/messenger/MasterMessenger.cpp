//
// Created by aaron on 3/1/24.
//

#include "MasterMessenger.h"

void MasterMessenger::listen() {

}

void MasterMessenger::hello(const int &rank) {

}

void MasterMessenger::goodbye() // will always be sent to broadcast
{

}

void MasterMessenger::sendWork(const int &rank, const std::vector<std::string> &work) {

}

std::vector<std::string> MasterMessenger::receiveResults() {

    return {};
}