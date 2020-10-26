#include <parser.hpp>

std::string Binary::accept(Visitor * visitor) {
    return visitor->visitBinary(std::shared_ptr<Binary>(this));
}
std::string Grouping::accept(Visitor * visitor) {
    return visitor->visitGrouping(std::shared_ptr<Grouping>(this));
}
std::string Unary::accept(Visitor *visitor ) {
    return visitor->visitUnary(std::shared_ptr<Unary>(this));
}
std::string Literal::accept(Visitor *visitor) {
    return visitor->visitLiteral(std::shared_ptr<Literal>(this));
}
