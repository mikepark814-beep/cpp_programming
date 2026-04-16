#include "Faculty.hpp"

// TODO: 아래 함수들을 구현하세요.

Faculty::Faculty(const std::string& name, int numMembers) : name(name) , numMembers(numMembers) {}

const std::string& Faculty::getName() const {
    return name;
}

int Faculty::getNumMembers() const {
    return numMembers;
}
