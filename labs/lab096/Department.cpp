#include "Department.hpp"
#include <iostream>
#include <algorithm>
#include <utility>

// Implement your code
Department::Department(std::string name) : name_(std::move(name)) {}

const std::string& Department::getName() const { return name_; }

void Department::setManager(std::unique_ptr<Manager> manager) {
    manager_ = std::move(manager);
}

void Department::addEmployee(std::unique_ptr<Employee> emp) {
    employees_.push_back(std::move(emp));
}

std::unique_ptr<Employee> Department::removeEmployee(Employee* emp) {
    auto it = std::find_if(employees_.begin(), employees_.end(),
                           [emp](const auto& e) { return e.get() == emp; });
    if (it == employees_.end()) return nullptr;
    auto result = std::move(*it);
    employees_.erase(it);
    return result;
}

void Department::printDetails(std::ostream& os) const {
    os << name_ << "\n";
    if (manager_) {
        os << "    |---Manager: " << manager_->getName() << " " << manager_->getId()
           << " (Annual: " << manager_->getSalary()
           << ", Monthly Pay: " << static_cast<long long>(manager_->calculatePay()) << ")\n";
    }
    for (const auto& emp : employees_) {
        emp->printDetails(os);
    }
}
