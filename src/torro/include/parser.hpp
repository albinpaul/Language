
#include <commonlibs.hpp>
#include <scanner.hpp>
#include <expressions.hpp>
#include <torro.hpp>
#ifndef _PARSER_HEADER_H
#define _PARSER_HEADER_H

class Parser
{
    std::vector <Token> tokens;
    int current = 0;
    spExpr equality();
    bool match(std::vector <TokenType> v);
    bool check(TokenType t);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    spExpr expression();
    spExpr comparison();
    spExpr term();
    spExpr factor();
    spExpr unary();
    spExpr primary();
    Token consume(TokenType t, std::string message);
    void synchronize();
    class ParseError: public std::runtime_error {
    public:
        explicit ParseError(const std::string& message);
        virtual ~ParseError() noexcept;
        virtual const char* what() const noexcept;
    protected:
        std::string msg_;
    };
    ParseError error(Token t, std::string message);
    public:
    spExpr parse();

    Parser(std::vector <Token> tokens);

};
#endif