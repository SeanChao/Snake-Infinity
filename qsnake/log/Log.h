#ifndef LOG_D
#define LOG_D
#include <iostream>
#include <string>
#include <sstream>

class Log {
   private:
    static std::string logStream;
    static void writeToFile();

   public:
    Log();
    inline static void d(std::string &info);
    static void d(char *);
    ~Log();
};


#endif  // LOG_D
