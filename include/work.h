#ifndef WORK_H
#define WORK_H

#include <vector>
#include <string>

class Work {
private:
    std::vector<std::string> wordlist; // vector of strings, the wordlist read in from the file
    std::vector<std::vector<std::string>> splitWork; // 2d vector of strings, one vector for each apprentice to search
    std::string wordlistName; // name of the wordlist file
    void readWordlist();

public:
    explicit Work(std::string wordlist);

    void split(int apprentices); // returns a 2d vector of strings, one vector for each apprentice to search

    std::vector<std::string> getWork(); // returns the next work chunk
    std::vector<std::string> getList(); // returns the wordlist itself
};


#endif