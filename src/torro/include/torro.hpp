#ifndef _INTERPRETOR
#define _INTERPRETOR
#include <scanner.hpp>
#include <parser.hpp>
class Interpreter{
        bool hasError = false;    
    public:
        static Interpreter * getInstance();
        static int runFile(const char * fileName);
        static int runPrompt();
        static int run(std::string &fileSource);
        static void error(int line,std::string message);
        static void error(Token token, std::string message);
};
// bool Interpreter::hasError =  false;
#endif