#include <commonlibs.hpp>
#include <scanner.hpp>
#ifndef _PARSER_HEADER_H
#define _PARSER_HEADER_H
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

// helper constant for the visitor #3
template<class> inline constexpr bool always_false_v = false;
class AstPrinter : Visitor { 
    
    std::string parenthesize(std::vector<std::variant <std::shared_ptr <Expr>,std::string >> vec) {
        std::stringstream  ss;
        Visitor *self = this;
        for (auto &v: vec)
        {
            std::visit([&](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::shared_ptr <Expr>>)
                ss << arg->accept(self);
            else if constexpr (std::is_same_v<T, std::string>)
                ss << arg;
            else if constexpr (std::is_same_v<T, std::monostate>)
                ss << "monostate";
            else 
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
            }, v);
        }
        return ss.str();                             
    }                   
    public:
    std::string print(std::shared_ptr<Expr> &expr) {                                            
        return expr->accept(this);                                          
    }
    std::string visitBinary(std::shared_ptr<Binary> binary) override {
        return parenthesize({binary->Operator->lexeme, binary->left, binary->right});
    }
    std::string visitGrouping(std::shared_ptr<Grouping> group) override{
        return parenthesize({"group",group->expression});  
    }
    std::string visitLiteral(std::shared_ptr<Literal> literal) override {                
      std::stringstream ss;
      std::visit([&](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int> 
            || std::is_same_v<T, std::string>
            || std::is_same_v<T, float>
            || std::is_same_v<T, bool>
            )
            ss << arg;
        else if constexpr (std::is_same_v<T, std::monostate>)
            ss << "monostate";
        else 
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
    
      },literal->literal);
      return ss.str();                            
    }   
    std::string visitUnary(std::shared_ptr<Unary> unary) override {                    
        return parenthesize({unary->Operator->lexeme, unary->expr});           
  }     

};

#endif