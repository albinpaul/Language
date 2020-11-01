#include <expressions.hpp>
std::string Binary::accept(std::shared_ptr <Visitor<std::string>> visitor) {
    std::shared_ptr<Binary> s = shared_from_this();
    return visitor->visitBinary(s);
}
std::string Grouping::accept(std::shared_ptr <Visitor<std::string>> visitor) {
    std::shared_ptr<Grouping> s = shared_from_this();
    return visitor->visitGrouping(s);
}

std::string Unary::accept(std::shared_ptr <Visitor<std::string>> visitor) {
     std::shared_ptr<Unary> s = shared_from_this();
    return visitor->visitUnary(s);
}
std::string Literal::accept(std::shared_ptr <Visitor<std::string>> visitor) {
    std::shared_ptr<Literal> s = shared_from_this();
    return visitor->visitLiteral(s);
}

LexemeVariant Binary::accept(std::shared_ptr <Visitor<LexemeVariant>> visitor) 
{
    std::shared_ptr<Binary> s = shared_from_this();
    return visitor->visitBinary(s);
}

LexemeVariant Grouping::accept(std::shared_ptr <Visitor<LexemeVariant>> visitor) {
    std::shared_ptr<Grouping> s = shared_from_this();
    return visitor->visitGrouping(s);
}

LexemeVariant Unary::accept(std::shared_ptr <Visitor<LexemeVariant>> visitor) {
     std::shared_ptr<Unary> s = shared_from_this();
    return visitor->visitUnary(s);
}



std::string AstPrinter::parenthesize(std::vector<StringAndExp> vec) {

        std::string ss;
        std::shared_ptr<Visitor> self = this->shared_from_this();
        for (auto &v: vec)
        {

            auto f = [&](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if  constexpr (std::is_same_v<T, std::shared_ptr <Expr>>)
            {    
                ss +=  arg->accept(self);
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {   
                ss += arg;
            }
            else if constexpr (std::is_same_v<T, std::monostate>)
                ss += "monostate";
            else 
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
            };
            std::visit(f, v);
        }
        return ss; 
}
