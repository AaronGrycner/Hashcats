#include "Logger.h"

#include <sstream>
#include <iostream>
#include <Node.h>

std::ofstream Logger::logFile;
std::string Logger::logName;
std::chrono::system_clock Logger::clock;
std::mutex Logger::mtx;

std::string Logger::getCurrentTime() {
    // Get the current time as std::chrono::system_clock::time_point
    const auto now = std::chrono::system_clock::now();

    // Convert to a time_t object
    const auto now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to tm struct
    const std::tm now_tm = *std::localtime(&now_c);

    // Use stringstream to format the time
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // Return the formatted time string
    return ss.str();
}

void Logger::init() {
    logName = "hashcats.log";
    logFile.open(logName);

    if (!logFile) {
        log("throwing log exception!!");
        throw;
    }

    system("mkdir -p logs");
}

void Logger::log(const std::string &message) {
    std::lock_guard<std::mutex> lock(mtx);
    const std::string log{getCurrentTime() + " PID: " + std::to_string(getpid()) + " - " + message + '\n'};
    logFile << log;
    std::cout << log;
}
