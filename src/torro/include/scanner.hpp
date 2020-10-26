#include <commonlibs.hpp>
#ifndef _SCANNER_HEADER_H
#define _SCANNER_HEADER_H
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

using LexemeVariant = std::variant <std::monostate,int,double, std::string> ;
class Token {
    public:
    const TokenType type;
    const std::string lexeme;
    const LexemeVariant literal;
    const int line;
    Token(TokenType type, std::string lexeme, int line);
    
    Token(TokenType type, std::string lexeme, LexemeVariant literal, int line);
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
    void addToken(TokenType type, LexemeVariant variant);
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




class Visitor;
class Expr{
    public:
    virtual std::string  accept(Visitor *) = 0;
};
class Binary : public Expr {
    public:
    Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> Operator, std::shared_ptr<Expr> right): left(left),Operator(Operator),right(right) {};    
    std::shared_ptr<Expr> left;
    std::shared_ptr<Token> Operator;
    std::shared_ptr<Expr> right;
    std::string accept(Visitor * );
};
class Grouping : public Expr {
    public:
    std::shared_ptr<Expr> expression;
    Grouping(std::shared_ptr<Expr> expression):expression(expression){};
    std::string accept(Visitor * );
};

class LiteralVisitor {
  public:
  std::string operator ()(std::string &v) {
    return v;
  }
  std::string operator ()(std::monostate &v) {
    return "void";
  }
  template <typename T>
  std::string operator ()(T v) {
    std::stringstream ss;
    ss << v;
    return ss.str();
  }
  
  
};

class Literal : public Expr {
    public:
    typedef std::variant<std::monostate,bool,int,float,std::string> LiteralType;
    LiteralType literal;
    Literal (LiteralType literal): literal(literal) {};
    Literal () {};
    std::string accept(Visitor *);
};

class Unary : public Expr {
    public:
    std::shared_ptr<Token> Operator;
    std::shared_ptr<Expr> expr;
    Unary(std::shared_ptr<Token> Operator,std::shared_ptr<Expr> expr): Operator(Operator), expr(expr) {};
    std::string accept(Visitor *);
};


class Visitor {
    public:
    virtual std::string visitBinary(std::shared_ptr<Binary> b) = 0 ;
    virtual std::string visitGrouping(std::shared_ptr<Grouping> b) = 0 ;
    virtual std::string visitLiteral(std::shared_ptr<Literal> b) = 0 ;
    virtual std::string visitUnary(std::shared_ptr<Unary> b) = 0 ;
    
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

    std::string handleCase(std::shared_ptr<Expr> &e) {
        return e->accept(this);
    };
    std::string handleCase(std::string s) {
        return s;
    };
    public:
    std::string print(std::shared_ptr<Expr> &expr) {                                            
        return expr->accept(this);                                          
    }
    std::string visitBinary(std::shared_ptr<Binary> binary) override {
        return parenthesize(binary->Operator->lexeme, binary->left, binary->right);
    }
    std::string visitGrouping(std::shared_ptr<Grouping> group) override{
        return parenthesize("group",group->expression);  
    }
    std::string visitLiteral(std::shared_ptr<Literal> literal) override {                
      if (!std::holds_alternative<std::monostate>(literal->literal)) 
        return "nil";
      return std::visit(LiteralVisitor{},literal->literal);                            
    }   
    std::string visitUnary(std::shared_ptr<Unary> unary) override {                    
        return parenthesize(unary->Operator->lexeme, unary->expr);           
  }     

};

#endif