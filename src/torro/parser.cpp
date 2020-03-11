#include <parser.hpp>
std::string Binary::accept(Visitor *visitor) {
    return visitor->visitBinary(this);
}
std::string Grouping::accept(Visitor *visitor) {
    return visitor->visitGrouping(this);
}
std::string Unary::accept(Visitor *visitor) {
    return visitor->visitUnary(this);
}
std::string Literal::accept(Visitor *visitor) {
    return visitor->visitLiteral(this);
}