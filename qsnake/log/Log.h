#ifndef LOG_D
#define LOG_D
#include <iostream>
#include <string>
#include <sstream>

class Log {
   private:
    static const bool enabled = true;
    static std::string logStream;
    static void writeToFile(std::string filename = "debug.log");

   public:
    Log();
    static void d(const std::string &info, std::string filename="debug.log");
    // static void d(char *);
    ~Log();
};


#endif  // LOG_D
