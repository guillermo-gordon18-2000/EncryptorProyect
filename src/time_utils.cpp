#include "time_utils.hpp"

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << localTime->tm_hour << ':'
       << std::setfill('0') << std::setw(2) << localTime->tm_min << ':'
       << std::setfill('0') << std::setw(2) << localTime->tm_sec;

    return ss.str();
}

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tm);
    return std::string(buffer);
}
