#include <scanner.hpp>

class Parser {
    std::vector <Token> tokens;
    int current = 0;
    bool isAtEnd() { return peek().type == EOF;};
    Token peek() { return tokens[current];};
    std::shared_ptr<Token> previous() { return std::shared_ptr<Token>(&tokens[current - 1]); };
    public:
    Parser(std::vector <Token> &tokens): tokens(tokens) {};
    std::shared_ptr<Expr> expression() { return equality(); };
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    bool match(int, ...);
    bool check(TokenType type);
    std::shared_ptr<Token> advance();
 
};