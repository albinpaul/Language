#include <iostream>
#include <torro.hpp>

int main(int argc, char * argv[]) {
    int error = 0;
    int a = 123;
    int b = 435;
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