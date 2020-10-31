#include <iostream>
#include <torro.hpp>
#include <expressions.hpp>
int main(int argc, char * argv[]) {
    int error = 0;
    
    Torro* instance = Torro::getInstance();
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