#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <unistd.h>

class Logger {
private:
    static std::chrono::system_clock clock;
    static std::string logName;
    static std::ofstream logFile;

    static std::string getCurrentTime();

public:
    static void init();
    static void log(const std::string &message);
};


#endif //LOGGER_H
