#include <interpretor.hpp>

LexemeVariant Interpretor::visitLiteral(std::shared_ptr<Literal> &literal) 
{
    return literal->literal;
}

LexemeVariant Interpretor::visitGrouping(std::shared_ptr<Grouping> &grouping) 
{
    return grouping->accept(shared_from_this()
    );
}


LexemeVariant Interpretor::visitUnary(std::shared_ptr<Unary> &unary) 
{
    LexemeVariant right;
    //  = evaluate(unary->accept(shared_from_this()));
    // switch(unary->Operator->type) {
    //     case MINUS:
    //         return - * right;
    // }
    // return 
    return right;
}

