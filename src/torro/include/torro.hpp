#ifndef _INTERPRETOR
#define _INTERPRETOR
#include <scanner.hpp>
#include <parser.hpp>
#include <interpretor.hpp>
class Torro{
        std::shared_ptr <Interpretor> interpretor = std::make_shared<Interpretor>();
        bool hasError = false;  
        bool hasRunTimeError = false;  
    public:
        static Torro * getInstance();
        static int runFile(const char * fileName);
        static int runPrompt();
        static int run(std::string &fileSource);
        static void error(int line,std::string message);
        static void error(Token token, std::string message);
        static void runTimeError(RunTimeError error);
};
// bool Torro::hasError =  false;
#endif