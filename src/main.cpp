#include <iostream>
#include <torro.hpp>
#include <parser.hpp>
int main(int argc, char * argv[]) {
    int error = 0;
    int a = 123;
    int b = 435;
    Token *minus=  new Token(TokenType::MINUS, "-", NULL, 1);
    Expr *left = new Unary(minus,new Literal(new LiteralWrapper<decltype(a)>(a) ));
    Expr *right = new Grouping(new Literal(new LiteralWrapper<decltype(b)>(b))) ;
    Token *token = new Token(TokenType::STAR, "*", NULL, 1);
    Expr *expression = new Binary(left,token,right);
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