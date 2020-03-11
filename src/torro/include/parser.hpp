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
    std::string visitBinary(Binary *b) ;
    std::string visitGrouping(Grouping *b) ;
    std::string visitLiteral(Literal *b) ;
    std::string visitUnary(Unary *b) ;
    
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

    template <class Expression>
    std::string handleCase(Expression e) {
        return e->accept(this);
    }
    template <>
    std::string handleCase(std::string s) {
        return s;
    }
    public:
    std::string print(Expr *expr) {                                            
        return expr->accept(this);                                          
    }
    std::string visitBinary(Binary *binary) {
        return parenthesize(binary->Operator->lexeme, binary->left, binary->right);
    }

};