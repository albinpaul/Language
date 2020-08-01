#include <iostream>
#include <torro.hpp>
#include <parser.hpp>

int main(int argc, char * argv[]) {
    int error = 0;
    int a = 123;
    int b = 435;
    std::shared_ptr <Token> minus=  std::make_shared<Token>(TokenType::MINUS, "-", nullptr, 1);
    std::shared_ptr<Literal> aliteral = std::make_shared<Literal>(a);
    std::shared_ptr<Literal> bliteral = std::make_shared<Literal>(b);
    std::shared_ptr<Expr> left = std::make_shared<Unary>(minus,aliteral);
    std::shared_ptr<Expr> right = std::make_shared<Grouping>(bliteral);
    std::shared_ptr<Token> token = std::shared_ptr<Token>(new Token(TokenType::STAR, "*", NULL, 1));
    std::shared_ptr<Expr> expression = std::make_shared<Binary>(left,token,right);
    std::cout << (new AstPrinter())->print(expression);
    return error;
    Interpreter iterpreter;
    if ( argc > 2 ) {
        std::cout << "Usage Torro [script] \n" ;
        error = 1;
    } else  if ( argc == 1) {
        error = iterpreter.runPrompt();
    } else {
        error = iterpreter.runFile(argv[1]);
    }
    return error;
}