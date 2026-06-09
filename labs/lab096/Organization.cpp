#include "Organization.hpp"
#include <iostream>
#include <algorithm>
#include <utility>

// Implement your code
Organization::Organization(std::string name) : name_(std::move(name)) {}

void Organization::addDept(std::unique_ptr<Department> dept) {
    departments_.push_back(std::move(dept));
}

void Organization::addEmpToDept(Department* dept, std::unique_ptr<Employee> emp) {
    dept->addEmployee(std::move(emp));
}

void Organization::setDeptManager(Department* dept, std::unique_ptr<Manager> manager) {
    dept->setManager(std::move(manager));
}

bool Organization::moveEmp(Department* from, Department* to, Employee* emp) {
    auto e = from->removeEmployee(emp);
    if (!e) return false;
    to->addEmployee(std::move(e));
    return true;
}

void Organization::print() const {
    std::cout << "Organization: " << name_ << "\n";
    for (const auto& dept : departments_) {
        dept->printDetails(std::cout);
    }
}
