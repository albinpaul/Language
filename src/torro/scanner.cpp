#include "scanner.hpp"
#include "torro.hpp"
#include <iostream>
Token::Token(TokenType type, std::string lexeme, LexemeVariant literal, int line) : 
    type(type),lexeme(lexeme),literal(literal),line(line){
}
Token::Token(TokenType type, std::string lexeme, int line) : 
    type(type),lexeme(lexeme),line(line){
}


// helper constant for the visitor #3
template<class> inline constexpr bool always_false_v = false;

std::ostream& operator<<(std::ostream& os, const Token& dt) {
    os << dt.type << " " << dt.lexeme << " ";
    std::visit(
        [&](auto &&arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            std::string returnValue = "";
            if constexpr (std::is_same_v<T,int> 
                || std::is_same_v<T, bool>
                || std::is_same_v<T, double>
            )
                os <<  std::to_string(arg);
           else if constexpr (std::is_same_v<T, std::string>)
                os << arg;
            else if constexpr (std::is_same_v<T, std::monostate>)
                os << "Lexeme is empty";
            else 
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
            return returnValue;
        },
        dt.literal
    );
    return os;
}
std::vector <Token> Scanner::scanTokens() {
    while(!isEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token(ENDOF, "", line));
    return tokens;
}
bool Scanner::isEnd() {
   return current >= source.size() ;
}
void Scanner::scanToken() {
    char c = advance();
    switch (c)
    {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;    
        case '{': addToken(LEFT_BRACE); break;     
        case '}': addToken(RIGHT_BRACE); break;    
        case ',': addToken(COMMA); break;          
        case '.': addToken(DOT); break;            
        case '-': addToken(MINUS); break;          
        case '+': addToken(PLUS); break;           
        case ';': addToken(SEMICOLON); break;      
        case '*': addToken(STAR); break;
        case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;      
        case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;    
        case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;      
        case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
        case '/':
            if (match('/')) {                                             
                while (peek() != '\n' && !isEnd()) advance();             
            } else {                                                      
                addToken(SLASH);                                            
            }     
             case ' ':                                    
        case '\r':                                   
        case '\t':                                   
            break;
        case '\n':                                   
            line++;                                    
            break; 
        case '"': string(); break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {                   
                identifier();                            
            } else {
                Interpreter::error(line,"unexpected character");
            }
            break;
    }
}
void Scanner::number() {
    while (isDigit(peek())) advance();
    if (peek() == '.' && isDigit(peekNext())) {               
      advance();                                              
      while (isDigit(peek())) advance();                      
    }                                                         

    double value =  atof (source.substr(start, current - start).c_str());
    addToken(NUMBER,value);
}

char Scanner::peekNext() {                         
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];              
} 
char Scanner::advance() {
    return source[current++];
}
char Scanner::peek() {           
    if (isEnd()) return '\0';   
    return source[current];
} 
bool Scanner::isDigit(char c) {
    return '0' <= c && c <= '9';
}
void Scanner::addToken(TokenType type) {                
    std::string text = source.substr(start, current - start);      
    tokens.push_back(Token(type, text, line));                                  
  }       
void Scanner::addToken(TokenType type, LexemeVariant variant) {
    std::string text = source.substr(start, current - start);      
    tokens.push_back(Token(type, text, variant, line));    
} 
bool Scanner::match(char expected) {
    if (isEnd())
        return false;
    if (source[current] != expected) 
        return false;
    current++;
    return true;
}      
void Scanner::string() {                                   
    while (peek() != '"' && !isEnd()) {                   
      if (peek() == '\n') line++;                           
      advance();                                            
    }
    if (isEnd()) {                                        
      Interpreter::error(line, "Unterminated string.");              
      return;                                               
    }                                                       
    advance();                                              
    std::string value = source.substr(start + 1, current - 1 - start - 1);
    addToken(STRING, value);                                
}
void Scanner::identifier() {                
    while (isAlphaNumeric(peek())) advance();
    std::string text = source.substr(start, current - start);
    auto it = keywords.find(text);           
    TokenType type =  (it == keywords.end()) ? IDENTIFIER : it -> second;
    addToken(type); 
  }    
bool  Scanner::isAlpha(char c) {       
    return (c >= 'a' && c <= 'z') ||      
           (c >= 'A' && c <= 'Z') ||      
            c == '_';                       
}

bool  Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);      
} 

  