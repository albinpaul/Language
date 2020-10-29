#include <iostream>
#include <torro.hpp>
#include <expressions.hpp>
int main(int argc, char * argv[]) {
    int error = 0;
    int a = 123;
    int b = 435;
    float c =45.67;
    
    std::shared_ptr<Expr> e = std::make_shared<Binary>( 
       std::make_shared<Unary> (
            std::make_shared<Token>(TokenType::MINUS, "-", 1),
            std::make_shared<Literal>(a)
            ),
        std::make_shared<Token>(TokenType::STAR, "*", 1),
        std::make_shared<Grouping>(std::make_shared<Literal>(c)) 
    );
    std::shared_ptr <AstPrinter> v = std::make_shared<AstPrinter> ();
    std::cout << (v)->print(e);
    return 0;
    Interpreter* instance = Interpreter::getInstance();
    if ( argc > 2 ) {
        std::cout << "Usage Torro [script] \n" ;
        error = 1;
    } else  if ( argc == 1) {
        error = instance->runPrompt();
    } else {
        error = instance->runFile(argv[1]);
    }
    return error;
}