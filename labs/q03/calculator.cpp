#include "calculator.hpp"

namespace calculator {

std::expected<double, Error> calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) {
                return std::unexpected(Error::DivisionByZero);
            }
            return a / b;
        default:
            return std::unexpected(Error::UnknownOperator);
    }
}

}
