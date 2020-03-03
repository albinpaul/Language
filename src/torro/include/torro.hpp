#include <string>
class interpreter{
    public:
    static int runFile(const char * fileName);
    static int runPrompt();
    static int run(const std::string &fileSource);
};