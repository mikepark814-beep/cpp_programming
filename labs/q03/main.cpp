#include "calculator.hpp"
#include <iostream>

int main() {
    double a;
    double b;
    char op;

    std::cout << "Enter expression (e.g., 10 / 5): ";
    if (!(std::cin >> a >> op >> b)) {
        std::cout << "Invalid input format.\n";
        return 1;
    }

    auto result = calculator::calculate(a, b, op);
    
    if (result) {
        std::cout << "Result: " << *result << '\n';
    } else {
        switch (result.error()) {
            case calculator::Error::DivisionByZero:
                std::cout << "Error: Division by zero\n";
                break;
            case calculator::Error::UnknownOperator:
                std::cout << "Error: Unknown operator '" << op << "'\n";
                break;
        }
        return 1;
    }

    return 0;
}
