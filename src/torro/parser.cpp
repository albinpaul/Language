#include <parser.hpp>

std::string Binary::accept(std::shared_ptr <Visitor> visitor) {
    std::shared_ptr<Binary> s(this);
    return visitor->visitBinary(s);
}
std::string Grouping::accept(std::shared_ptr <Visitor> visitor) {
    std::shared_ptr<Grouping> s(this);
    return visitor->visitGrouping(s);
}
std::string Unary::accept(std::shared_ptr <Visitor> visitor) {
    std::shared_ptr<Unary> s(this);
    return visitor->visitUnary(s);
}
std::string Literal::accept(std::shared_ptr <Visitor> visitor) {
    std::shared_ptr<Literal> s(this);
    return visitor->visitLiteral(s);
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
                std::cout << "expr" << std::endl;
            
                ss += arg->accept(self);
                
                std::cout << "afterexpr" << std::endl;
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
