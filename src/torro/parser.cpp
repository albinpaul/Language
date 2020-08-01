#include <parser.hpp>



std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();

    while (match(2,BANG_EQUAL, EQUAL_EQUAL)) {
        ;
      std::shared_ptr<Token> token_ptr =  previous();
      std::shared_ptr<Expr> right = comparison();
      expr = std::make_shared <Binary>(expr, token_ptr, right);
    }
    return expr;
}


 bool Parser::match(int num_args,...) {
    va_list args;
    TokenType type;
    va_start(args,num_args);
    for(int i=0;i<num_args; ++i) {
        type = va_arg(args, TokenType);
        if (check(type)) {
        advance();
        return true;
      }
    }
    return false;
}
std::shared_ptr<Expr> Parser::comparison() {
    // std::shared_ptr<Expr> expr = addition();
    std::shared_ptr<Expr> expr;
    while (match(3,GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
      std::shared_ptr<Token> token_ptr =  previous();
    //   std::shared_ptr<Expr> right = addition();
    //   expr = std::make_shared<Binary> (expr, operator, right);
    }

    return expr;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}
std::shared_ptr<Token> Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}


