#include <torro.hpp>
#include <scanner.hpp>
#include <iostream>
#include <fstream>
int Torro::runPrompt() {
    std::cout << "Running Torro Interpretor" << std::endl;
    int error = 0;
    for(std::string line;;) {
        std::cout << ">->->" ;
        std::getline(std::cin,line);
        error = run(line);
    }
    return error;

}
int Torro::runFile(const char * fileName) {
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
int Torro::run(std::string &fileSource) {
    Scanner scan(fileSource);
    std::vector <Token> tokens = scan.scanTokens();
    Parser parser(tokens);
    spExpr expression =  parser.parse();
   
    if (Torro::getInstance() -> hasError) {
        exit(65);
    }
    Torro::getInstance()->interpretor->interpret(expression);
    if (Torro::getInstance() -> hasRunTimeError) {
        exit(70);
    }
    std::cout << std::make_shared<AstPrinter> ()->print(expression) << std::endl;
    return 0;
}
void Torro::error(int line,std::string message) {
    std::cerr <<"Line is " << line << " " << message << std::endl;
}

void  Torro::error(Token token, std::string message) {
    if (token.type == TokenType::ENDOF) {
      error(token.line, " at end" + message);
    } else {
      error(token.line, " at '" + token.lexeme + "'" +  message);
    }
    Torro::getInstance()->hasError = true;
}
Torro * Torro::getInstance(){
    static Torro * instance = new Torro();
    return instance;
}



void Torro::runTimeError(RunTimeError error) 
{
    std::cerr << error.what() << std::endl;
    Torro::getInstance()->hasRunTimeError = true;
}
