
#include <commonlibs.hpp>
#include <scanner.hpp>
#include <expressions.hpp>
#include <torro.hpp>
#ifndef __INTERPRETOR_H__
#define __INTERPRETOR_H__

class RunTimeError: public std::runtime_error {
    public:
        explicit RunTimeError(spToken token, std::string &message);
        explicit RunTimeError(spToken token, const char * message);
        virtual ~RunTimeError() noexcept;
        virtual const char* what() const noexcept;
    protected:
        std::string msg_;
        spToken token;
};

class Interpretor: public Visitor<LexemeVariant> {
    LexemeVariant visitGrouping(std::shared_ptr<Grouping> &grouping) override;
    LexemeVariant visitLiteral(std::shared_ptr<Literal> &literal) override;
    LexemeVariant visitUnary(std::shared_ptr<Unary> &unary) override;
    LexemeVariant visitBinary(std::shared_ptr<Binary> &binary) override;
    bool isTruthy(LexemeVariant &l);
    bool isEqual(LexemeVariant &a, LexemeVariant &b);
    LexemeVariant evaluate(std::shared_ptr<Expr> &e);
    void checkNumberOperands(spToken operand, LexemeVariant &left, LexemeVariant &right);
    public:
    void interpret(spExpr expr);
};
#endif // __INTERPRETOR_H__