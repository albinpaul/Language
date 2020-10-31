#include "parser.hpp"

Parser::Parser(std::vector <Token> tokens) : tokens(tokens) {
    
}
spExpr Parser::expression() {
    return equality();
}

spExpr Parser::equality() 
{
    spExpr expr = comparison();
    while(match({BANG_EQUAL, EQUAL_EQUAL}))
    {
        Token operator_ = previous();
        spExpr right = comparison();
        expr = std::make_shared<Binary>(expr, std::make_shared<Token>(operator_), right);
    }
    return expr;
}


bool Parser::match(std::vector <TokenType> v) 
{
    for(auto type: v) {
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}


bool Parser::check(TokenType type) 
{
    if (isAtEnd()) return false;
    return peek().type == type;
}


Token Parser::advance() 
{
    if (!isAtEnd()) current++;
    return previous();
}


bool Parser::isAtEnd() 
{
    return peek().type == ENDOF;
}


Token Parser::peek() 
{
    return tokens.at(current);
}


Token Parser::previous() 
{
    return tokens.at(current - 1);
}


spExpr Parser::comparison() 
{
    spExpr expr = term();
    while(match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token operator_ = previous();
        spExpr right = term();
        expr =  std::make_shared<Binary>(expr, std::make_shared<Token>(operator_), right);
    }
    return expr;
}



spExpr Parser::term() 
{
    spExpr expr = factor();
    while(match({MINUS, PLUS})) {
        Token operator_ = previous();
        spExpr right = factor();
        expr =  std::make_shared<Binary>(expr, std::make_shared<Token>(operator_), right);    
    }
    return expr;
}


spExpr Parser::factor() 
{
    spExpr expr = unary();
    while(match({SLASH, STAR})) {
        Token operator_ = previous();
        spExpr right = unary();
        expr =  std::make_shared<Binary>(expr, std::make_shared<Token>(operator_), right);    
    }
    return expr;
}

spExpr Parser::unary() 
{
    if (match({BANG, MINUS})) {
        Token operator_ = previous();
        spExpr right = unary();
        return std::make_shared<Unary>(std::make_shared<Token>(operator_), right);
    }
    return primary();
}

spExpr Parser::primary() 
{
    if (match({FALSE})) return std::make_shared<Literal>(false);
    if (match({TRUE})) return std::make_shared<Literal>(true);
    if (match({NIL})) return std::make_shared<Literal>();
    if (match({NUMBER, STRING})){
        return std::make_shared<Literal>(previous().literal);
    }
    if(match({LEFT_PAREN})) {
        spExpr expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after Expression.");
        return std::make_shared<Grouping>(expr);
    }
    throw error(peek(), "\nExpected expression,");
}


Token Parser::consume(TokenType t, std::string message) 
{
    if (check(t)) return advance();
    throw error(peek(), message);    
}

Parser::ParseError Parser::error(Token t, std::string message) 
{
    Torro::error(t, message);
    return ParseError(message);
}


const char* Parser::ParseError::what() const noexcept
{
    return msg_.c_str();

}


Parser::ParseError::ParseError(const std::string& message): msg_(message), std::runtime_error(message)
{

}



Parser::ParseError::~ParseError() noexcept
{

}


void Parser::synchronize() 
{
    advance();

    while (!isAtEnd()) {
      if (previous().type == SEMICOLON) return;

      switch (peek().type) {
        case CLASS:
        case FUN:
        case VAR:
        case FOR:
        case IF:
        case WHILE:
        case PRINT:
        case RETURN:
          return;
      }

      advance();
    }
}


spExpr Parser::parse() 
{
    try{
        return expression();
    } catch(ParseError e) {
        return nullptr;
    }
}
