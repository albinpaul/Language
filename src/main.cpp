#include <iostream>
#include <torro.hpp>
int main(int argc, char * argv[]) {
    int error = 0;
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