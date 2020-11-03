#ifndef __INTERPRETOR_H__
#define __INTERPRETOR_H__

#include <commonlibs.hpp>
#include <scanner.hpp>
#include <expressions.hpp>
class Interpretor: public Visitor<LexemeVariant> {
    LexemeVariant visitGrouping(std::shared_ptr<Grouping> &grouping) override;
    LexemeVariant visitLiteral(std::shared_ptr<Literal> &literal) override;
    LexemeVariant visitUnary(std::shared_ptr<Unary> &unary) override;
    LexemeVariant visitBinary(std::shared_ptr<Binary> &binary) override;
    bool isTruthy(LexemeVariant &l);
    bool isEqual(LexemeVariant &a, LexemeVariant &b);
    LexemeVariant evaluate(std::shared_ptr<Expr> &e);
};
#endif // __INTERPRETOR_H__