#include <scanner.hpp>
class Expr{
};
class Binary : public Expr {
    public:
    Binary(Expr *left, Token *Operator, Expr *right): left(left),Operator(Operator),right(right) {};    
    Expr *left;
    Token *Operator;
    Expr *right;

};
class Grouping : public Expr {
    public:
    Expr *expression;
    Grouping(Expr *expression):expression(expression){};
};

class Literal : public Expr {
    public:
    void * literal;
    Literal (void *literal): literal(literal) {};
};

class Unary : public Expr {
    public:
    Token *Operator;
    Expr *expr;
    Unary(Token *Operator,Expr *expr): Operator(Operator), expr(expr) {};
};