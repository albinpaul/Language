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
LexemeVariant Interpretor::evaluate(std::shared_ptr<Expr> &e) {
    return e->accept(shared_from_this());
}

LexemeVariant Interpretor::visitUnary(std::shared_ptr<Unary> &unary) 
{
    LexemeVariant right = evaluate(unary->expr);
    switch(unary->Operator->type) {
        case BANG:
            return !isTruthy(right);
        case MINUS:
            return std::visit([](auto &&arg) -> LexemeVariant {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
                    return LexemeVariant(-1 * arg);
                }
                return LexemeVariant();
            },right);
    }
    return LexemeVariant();
}


bool Interpretor::isTruthy(LexemeVariant &l) 
{
    return std::visit([](auto &&arg) -> bool {
         using T = std::decay_t<decltype(arg)>;
         if constexpr (std::is_same_v<T, std::monostate>) {
            return false;
         } 
         else if constexpr (std::is_same_v<T, bool>)
         {
            return bool(arg);
         }
         return true;
    }, l);
}


LexemeVariant Interpretor::visitBinary(std::shared_ptr<Binary> &binary) 
{
    LexemeVariant left = evaluate(binary->left);
    LexemeVariant right = evaluate(binary->right);
    switch(binary->Operator->type) {
        case MINUS:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 - (double)arg2);
                }
                if constexpr (std::is_same_v<T1, std::string> && std::is_same_v<T2, std::string>) {
                    return LexemeVariant(static_cast<std::string> (arg1) + static_cast<std::string>(arg2));
                }
                return LexemeVariant();
    },left,right);
        case SLASH:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 / (double)arg2);
                }
                return LexemeVariant();
            },left,right);
        case STAR:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 * (double)arg2);
                }
                return LexemeVariant();
            },left,right);
        case GREATER:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 > (double)arg2);
                }
                return LexemeVariant();
            },left,right);
        case GREATER_EQUAL:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 >= (double)arg2);
                }
                return LexemeVariant();
            },left,right);
        
        case LESS:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 < (double)arg2);
                }
                return LexemeVariant();
            },left,right);
        
        case LESS_EQUAL:
            return std::visit([](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 <= (double)arg2);
                }
                return LexemeVariant();
            },left,right);
        
        case BANG_EQUAL: return !isEqual(left, right);
        case EQUAL_EQUAL: return isEqual(left, right);

    }
    return LexemeVariant();
}



bool Interpretor::isEqual(LexemeVariant &a, LexemeVariant &b) 
{
    if (std::holds_alternative<std::monostate>(a)) return false;
    return a == b;
}

