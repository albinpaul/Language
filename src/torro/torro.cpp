#include <torro.hpp>
#include <iostream>
#include <fstream>
int interpreter::runPrompt() {
    std::cout << "Running Torro Interpretor" << std::endl;
    int error = 0;
    for(std::string line;;) {
        std::cout << ">->->" ;
        std::getline(std::cin,line);
        error = run(line);
        if (error)
            break;
    }
    return error;

}
int interpreter::runFile(const char * fileName) {
    std::ifstream inputStream(fileName);
    int error = 0;
    std::string fileSource;
    if (inputStream.good()) {
        inputStream.seekg(0,std::ios::end);
        fileSource.reserve(inputStream.tellg());
        inputStream.seekg(0,std::ios::beg);
        fileSource.assign(std::istreambuf_iterator<char>(inputStream),std::istreambuf_iterator<char>());
        run(fileSource);
    }else {
        std::cerr << "Could not open file" << fileName << std::endl;
    }
    return error;
}
int interpreter::run(std::string &fileSource) {
    return 0;
}