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
            return std::visit([&](auto &&arg) -> LexemeVariant {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
                    return LexemeVariant(-1 * arg);
                }
               throw new RunTimeError(unary->Operator, "Operands must be numbers");
            //    return LexemeVariant();
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
        case PLUS:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
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
                throw new RunTimeError(binary->Operator, "Operands must be numbers");
    },left,right);
        case MINUS:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 - (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");

    },left,right);
        case SLASH:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 / (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");
            },left,right);
        case STAR:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 * (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");
            },left,right);
        case GREATER:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 > (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");
            },left,right);
        case GREATER_EQUAL:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 >= (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");
            },left,right);
        
        case LESS:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 < (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");
            },left,right);
        
        case LESS_EQUAL:
            return std::visit([&](auto &&arg1, auto &&arg2) -> LexemeVariant {
                using T1 = std::decay_t<decltype(arg1)>;
                using T2 = std::decay_t<decltype(arg2)>;
                if constexpr ((std::is_same_v<T1, int> 
                    || std::is_same_v<T1, double>)
                    && (std::is_same_v<T2, int>
                    || std::is_same_v<T2, double>)
                    ) {
                    return LexemeVariant((double)arg1 <= (double)arg2);
                }
                 throw new RunTimeError(binary->Operator, "Operands must be numbers");
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


void Interpretor::checkNumberOperands(spToken operator_, LexemeVariant &left, LexemeVariant &right) 
{
    bool ok = true;
    if (! (std::holds_alternative<double> (left) || std::holds_alternative<int>(left)) )
        ok = false;
    if (! (std::holds_alternative<double> (right) || std::holds_alternative<int>(right)) )
        ok = false;
    if (ok)
        return;
    throw new RunTimeError(operator_, "Operands must be numbers");
}

RunTimeError::RunTimeError(spToken token, std::string& message)
    : token(token), msg_(message), std::runtime_error(message)
{

}


RunTimeError::~RunTimeError() noexcept
{

}


const char* RunTimeError::what() const noexcept
{
    return msg_.c_str();
}


RunTimeError::RunTimeError(spToken token, const char * message)
    :msg_(message), token(token), std::runtime_error(message)
{

}
