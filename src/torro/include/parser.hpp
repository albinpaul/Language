#include <scanner.hpp>
#include <sstream>
#include <cstdarg>

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
        ss << "(" << handleCase(t) << ")";
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
        return *static_cast<std::string*>(literal->literal);                                    
    }   
    std::string visitUnary(Unary *unary) override {                    
        return parenthesize(unary->Operator->lexeme, unary->expr);           
  }     

};