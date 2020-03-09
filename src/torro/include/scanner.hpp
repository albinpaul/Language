#include <string>
#include <ostream>
#include <vector>
#include <unordered_map>
enum TokenType {
    // Single-character tokens.                      
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, 

  // One or two character tokens.                  
  BANG, BANG_EQUAL,                                
  EQUAL, EQUAL_EQUAL,                              
  GREATER, GREATER_EQUAL,                          
  LESS, LESS_EQUAL,                                

  // Literals.                                     
  IDENTIFIER, STRING, NUMBER,                      

  // Keywords.                                     
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,  
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,    
  ENDOF  
};

class Token {
    const TokenType type;
    const std::string lexeme;
    const void * literal;
    const int line;
  public:
    Token(TokenType type, std::string lexeme, void * literal, int line);
    friend std::ostream& operator<<(std::ostream& os, const Token& dt);
};


class Scanner {
    const std::string source;
    std::vector <Token> tokens;
    unsigned int start = 0;
    unsigned int current = 0;
    unsigned int line = 1;
    std::unordered_map <std::string,TokenType> keywords {
      {"and",    AND},                       
      {"class",  CLASS},                     
      {"else",   ELSE},                      
      {"false",  FALSE},                     
      {"for",    FOR},                       
      {"fun",    FUN},                       
      {"if",     IF},                        
      {"nil",    NIL},                       
      {"or",     OR},                        
      {"print",  PRINT},                     
      {"return", RETURN},                    
      {"super",  SUPER},                     
      {"this",   THIS},                      
      {"true",   TRUE},                      
      {"var",    VAR},                       
      {"while",  WHILE} 
    };
  public:
    Scanner(std::string source): source(source) {};
    std::vector <Token> scanTokens() ;
    bool isEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type) ;
    void addToken(TokenType type, void * literal);
    bool match(char c);
    char peek();
    void string();
    bool isDigit(char c);
    void number();
    char peekNext();
    void identifier();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
};
