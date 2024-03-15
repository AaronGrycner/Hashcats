#include "Logger.h"

#include <sstream>
#include <iostream>

std::ofstream Logger::logFile;
std::string Logger::logName;
std::chrono::system_clock Logger::clock;

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
    logName = "logs/" + getCurrentTime() + ".log";
    logFile.open(logName);

    system("rm logs/*");

    if (!logFile) {
        throw;
    }

    system("mkdir -p logs");
}

void Logger::log(const std::string &message) {
    logFile << getCurrentTime() << " - " << message << std::endl;
    std::cout << getCurrentTime() << "PID: " << getpid() << " - " << message << std::endl;
}
