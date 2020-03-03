#include <iostream>
#include <torro.hpp>
int main(int argc, char * argv[]) {
    int error = 0;
    if ( argc > 2 ) {
        std::cout << "Usage Torro [script] \n" ;
        error = 1;
    } else  if ( argc == 1) {
        error = interpreter::runPrompt();
    } else {
        error = interpreter::runFile(argv[1]);
    }
    return error;
}