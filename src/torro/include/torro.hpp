#include <string>

#ifndef _INTERPRETOR
#define _INTERPRETOR
    class Interpreter{
            bool hasError = false;
        public:
            static int runFile(const char * fileName);
            static int runPrompt();
            static int run(std::string &fileSource);
            static void error(int line,std::string message);
}   ;
// bool Interpreter::hasError =  false;
#endif