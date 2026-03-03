#pragma once

#include <expected>
#include <string>

namespace calculator {

enum class Error {
    DivisionByZero,
    UnknownOperator
};

std::expected<double, Error> calculate(double a, double b, char op);

}
