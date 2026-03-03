#include "multiply.hpp"
#include <iostream>

int main() {
    double a;
    double b;

    std::cout << "Enter two numbers to multiply: ";
    if (!(std::cin >> a >> b)) {
        std::cout << "Invalid input format.\n";
        return 1;
    }

    double result = multiply::multiply(a, b);
    std::cout << a << " * " << b << " = " << result << '\n';

    return 0;
}
