#include <string>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstdarg>

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
    public:
    const TokenType type;
    const std::string lexeme;
    const void * literal;
    const int line;

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



class Type {
    public:
    virtual std::string to_string() = 0;
};

template <typename T>
class LiteralWrapper : public Type {
    T a;
    public:
    LiteralWrapper(T a):a(a) {};
    std::string to_string() override{
        std::stringstream ss;
        ss << a ;
        return ss.str();
    }
};


class Visitor;
class Expr{
    public:
    virtual std::string  accept(Visitor * ) = 0;
};
class Binary : public Expr {
    public:
    Binary(Expr *left, Token *Operator, Expr *right): left(left),Operator(Operator),right(right) {};    
    Expr *left;
    Token *Operator;
    Expr *right;
    std::string accept(Visitor *);
};
class Grouping : public Expr {
    public:
    Expr *expression;
    Grouping(Expr *expression):expression(expression){};
    std::string accept(Visitor *);
};

class Literal : public Expr {
    public:
    void * literal;
    Literal (void *literal): literal(literal) {};
    std::string accept(Visitor *);
};

class Unary : public Expr {
    public:
    Token *Operator;
    Expr *expr;
    Unary(Token *Operator,Expr *expr): Operator(Operator), expr(expr) {};
    std::string accept(Visitor * );
};


class Visitor {
    public:
    virtual std::string visitBinary(Binary *b) = 0 ;
    virtual std::string visitGrouping(Grouping *b) = 0 ;
    virtual std::string visitLiteral(Literal *b) = 0 ;
    virtual std::string visitUnary(Unary *b) = 0 ;
    
};
class AstPrinter : Visitor { 
    
    template <class Head,class ...Args>
    std::string parenthesize(Head head,Args ...args) {
        std::stringstream  ss;
        ss << "(" << handleCase(head) << " ";
        ss << parenthesize(args...);
        ss << ")";
        return ss.str();                             
    }                   
    template <class T>
    std::string parenthesize(T t) {
        std::stringstream  ss;
        ss << handleCase(t);
        return ss.str();                             
    }                   

    std::string handleCase(Expr *e) {
        return e->accept(this);
    };
    std::string handleCase(std::string s) {
        return s;
    };
    public:
    std::string print(Expr *expr) {                                            
        return expr->accept(this);                                          
    }
    std::string visitBinary(Binary *binary) override {
        return parenthesize(binary->Operator->lexeme, binary->left, binary->right);
    }
    std::string visitGrouping(Grouping *group) override{
        return parenthesize("group",group->expression);  
    }
    std::string visitLiteral(Literal *literal) override {                
        if (literal->literal == NULL) return "nil";                            
        return static_cast<Type*>(literal->literal) ->to_string();                                    
    }   
    std::string visitUnary(Unary *unary) override {                    
        return parenthesize(unary->Operator->lexeme, unary->expr);           
  }     

};

