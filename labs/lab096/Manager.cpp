#include "Manager.hpp"
#include <utility>

// Implement your code
Manager::Manager(std::string name, int salary)
    : Employee(std::move(name), salary) {}

double Manager::calculatePay() const {
    return static_cast<double>((long long)getSalary() * 11 / 10 / 12);
}
