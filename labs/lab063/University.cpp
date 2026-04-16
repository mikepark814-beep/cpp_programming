#include "University.hpp"
#include <iostream>

// TODO: 아래 함수들을 구현하세요.

University::University(const std::string& name) : name(name) {}
    // departments는 vector 기본 생성자로 빈 상태가 자동 초기화됩니다.

void University::addDepartment(const Department& dept) {
    departments.push_back(dept);
}

void University::printInfo() const {
    // 출력 형식:
    // "University Name: <name>\n"
    // "Number of Departments: <departments.size()>\n"
    // 각 학과마다:
    //   "\n"  (빈 줄)
    //   "Department Name: <name>\n"
    //   faculty가 nullptr:  "Faculty Name: N/A\n" + "Number of Faculty Members: N/A\n"
    //   faculty가 있음:     "Faculty Name: <name>\n" + "Number of Faculty Members: <num>\n"
    // 힌트: auto f = dept.getFaculty(); if (f) { ... } else { ... }
    std::cout << "University Name: " << name << "\n";
    std::cout << "Number of Departments: " << departments.size() << "\n";
   
    for (const auto& dept : departments) {
        std::cout << "\n";
        std::cout << "Department Name: " << dept.getName() << "\n";

        auto f = dept.getFaculty();

        if (f) {
            std::cout << "Faculty Name: " << f -> getName() << "\n";
            std::cout << "Number of Faculty Members: " << f -> getNumMembers() << "\n";
        }

        else {
            std::cout << "Faculty Name: N/A" << "\n";
            std::cout << "Number of Faculty Member: N/A" << "\n";
        }
    } 
}
