#include "log.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

std::string Log::logStream = "";

const std::string currentDateTime() {
    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    std::string dt = ctime(&now);
    dt.replace(0, 4, ""); // cut the weekday
    dt.replace(dt.length()-1, 1, ""); // cut the \n
    return dt;
}

void Log::d(const std::string &info) {
    // auto currentTime = std::chrono::system_clock::now();
    logStream += "[" + currentDateTime() + "] [debug]\t" + info + '\n';
    writeToFile();
}

// void Log::d(char *info) {
//     logStream += "[" + currentDateTime() + "] \t"  + info + '\n';
//     writeToFile();
// }

void Log::writeToFile() {
    std::ofstream fileOutPutStream("debug.log", std::ios_base::app);
    fileOutPutStream << logStream;
    logStream.clear();
    fileOutPutStream.close();
}
