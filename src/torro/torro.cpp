#include <torro.hpp>
#include <scanner.hpp>
#include <iostream>
#include <fstream>
int Interpreter::runPrompt() {
    std::cout << "Running Torro Interpretor" << std::endl;
    int error = 0;
    for(std::string line;;) {
        std::cout << ">->->" ;
        std::getline(std::cin,line);
        error = run(line);
    }
    return error;

}
int Interpreter::runFile(const char * fileName) {
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
int Interpreter::run(std::string &fileSource) {
    Scanner scan(fileSource);
    std::vector <Token> tokens = scan.scanTokens();
    Parser parser(tokens);
    spExpr expression =  parser.parse();
    for(auto &it:tokens) {
        std::cout << it << std::endl;
    }
    if (Interpreter::getInstance() -> hasError) {
        exit(65);
    }
    std::make_shared<AstPrinter> ()->print(expression);
    return 0;
}
void Interpreter::error(int line,std::string message) {
    std::cerr <<"Line is " << line << " " << message << std::endl;
}

void  Interpreter::error(Token token, std::string message) {
    if (token.type == TokenType::ENDOF) {
      error(token.line, " at end" + message);
    } else {
      error(token.line, " at '" + token.lexeme + "'" +  message);
    }
    Interpreter::getInstance()->hasError = true;
}
Interpreter * Interpreter::getInstance(){
    static Interpreter * instance = new Interpreter();
    return instance;
}