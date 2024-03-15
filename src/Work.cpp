#include "Work.h"

#include <fstream>
#include <utility>

Work::Work(std::string wordlist) : wordlistName(std::move((wordlist))){
    readWordlist();
}

void Work::readWordlist() {
    std::ifstream file(wordlistName);
    std::string temp;

    if (!file) {
        throw std::runtime_error("Could not open wordlist");
    }

    while (file) {
        getline(file, temp);
        wordlist.emplace_back(temp);
    }
}

void Work::split(int apprentices) {
    int i{};

    for (const auto& word : wordlist) {
        splitWork[i].emplace_back(word);
        i = (i + 1) % apprentices;
    }
}

std::vector<std::string> Work::getWork() {
    std::vector<std::string> work = splitWork.back();

    splitWork.pop_back();

    return work;
}
