#include "calc.h"
#include <iostream>

int main() {
    // 1) nullptr 가드 테스트: 값이 변하면 안 됨
    int probe = 42;
    transform(nullptr, &probe);
    transform(&probe, nullptr);
    std::cout << "after nullptr test: " << probe << '\n';  // 42

    // 2) 일반 테스트: stdin으로 a, b 입력
    int a, b;
    std::cin >> a >> b;
    transform(&a, &b);
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    return 0;
}
