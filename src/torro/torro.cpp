#include <torro.hpp>
#include <iostream>
#include <fstream>
int interpreter::runPrompt() {
    std::cout << "Running Torro Interpretor" << std::endl;
    std::cout << ">->->";
    int error = 0;
    for(std::string line;std::getline(std::cin,line);) {
        std::cout << ">->->" ;
        error = run(line);
        if (error)
            break;
    }
    return error;

}
int interpreter::runFile(const char * fileName) {
    std::ifstream inputStream(fileName);
    int error = 0;
    if (inputStream.good()) {

    }else {
        std::cerr << "Could not open file" << fileName << std:: endl;
    }
    return error;
}
int interpreter::run(const std::string &fileSource) {
    return 0;
}