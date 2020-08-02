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
        type = static_cast <TokenType>(va_arg(args, int));
        if (check(type)) {
        advance();
        return true;
      }
    }
    return false;
}
std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = addition();
    while (match(3,GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
      std::shared_ptr<Token> token_ptr =  previous();
      std::shared_ptr<Expr> right = addition();
      expr = std::make_shared<Binary> (expr, token_ptr, right);
    }

    return expr;
}

std::shared_ptr <Expr>  Parser::addition() {
    std::shared_ptr <Expr> expr = multiplication();

    while (match(2,MINUS, PLUS)) {
      std::shared_ptr <Token> token_ptr = previous();
      std::shared_ptr <Expr> right = multiplication();
      expr = std::make_shared <Binary>(expr, token_ptr, right);
    }

    return expr;
}

std::shared_ptr <Expr>  Parser::multiplication() {
    std::shared_ptr <Expr> expr = unary();

    while (match(2,SLASH, STAR)) {
      std::shared_ptr <Token> token_ptr = previous();
      std::shared_ptr <Expr> right = unary();
      expr = std::make_shared <Binary>(expr, token_ptr, right);
    }

    return expr;
}
std::shared_ptr <Expr>  Parser::unary() {
    if (match(2, BANG, MINUS)) {
      std::shared_ptr <Token> token_ptr = previous();
      std::shared_ptr <Expr> right = unary();
      return std::make_shared <Unary>(token_ptr, right);
    }

    return primary();
}
std::shared_ptr <Expr> Parser::primary() {
    if (match(1,FALSE)) return  std::make_shared <Literal>(false);
    if (match(1,TRUE)) return std::make_shared <Literal>(true);
    if (match(1,NIL)) return std::make_shared <Literal>();

    if (match(2,NUMBER, STRING)) {
      return std::make_shared <Literal>(previous()->literal);
    }

    if (match(LEFT_PAREN)) {
      std::shared_ptr <Expr> expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return std::make_shared <Grouping>(expr);
    }
    throw ParseError("invalid file or line");
}

std::shared_ptr <Token> Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


Parser::ParseError Parser::error(Token token, std::string message) {
    Interpreter::error(token, message);
    return Parser::ParseError("gofor");
}


bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}
std::shared_ptr<Token> Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}


char const * Parser::ParseError::what() const throw() {
    return std::exception::what();
}