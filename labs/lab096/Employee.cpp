#include "Employee.hpp"
#include <utility>

// Implement your code
int Employee::nextId_ = 1;

Employee::Employee(std::string name, int salary)
    : id_(nextId_++), name_(std::move(name)), salary_(salary) {}

std::string Employee::getName() const { return name_; }
int Employee::getId() const { return id_; }
int Employee::getSalary() const { return salary_; }

double Employee::calculatePay() const {
    return static_cast<double>(salary_ / 12);
}

void Employee::printDetails(std::ostream& os) const {
    os << "    |---" << name_ << " " << id_
       << " (Annual: " << salary_
       << ", Monthly Pay: " << static_cast<long long>(calculatePay()) << ")\n";
}
