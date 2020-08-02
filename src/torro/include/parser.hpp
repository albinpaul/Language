#include <exception>
#include <torro.hpp>
class Parser {
    
    std::vector <Token> tokens;
    int current = 0;
    bool isAtEnd() { return peek().type == EOF;};
    Token peek() { return tokens[current];};
    std::shared_ptr<Token> previous() { return std::shared_ptr<Token>(&tokens[current - 1]); };
    public:
    class ParseError : std::runtime_error {
        public:
        ParseError(std::string message) : std::runtime_error(message.c_str())  {};
        virtual char const * what() const throw ();
    };
    Parser(std::vector <Token> &tokens): tokens(tokens) {};
    std::shared_ptr<Expr> expression() { return equality(); };
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr <Expr> addition();
    std::shared_ptr <Expr> multiplication();
    std::shared_ptr <Expr> unary();
    std::shared_ptr <Expr> primary();
    std::shared_ptr <Token> consume(TokenType type, std::string message);
    std::shared_ptr<Token> advance();
    bool match(int, ...);
    bool check(TokenType type);
    ParseError error(Token token, std::string message);
};