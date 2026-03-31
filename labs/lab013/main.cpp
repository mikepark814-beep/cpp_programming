#include "pointer.h"
#include <iostream>

int main() {
    int a, b;
    int* pA = &a;
    int* pB = &b;
    int probe = 0;

    update(nullptr, &probe);
    update(&probe, nullptr);
    std::cin >> *pA >> *pB;
    update(pA, pB);
    std::cout << a << '\n';
    std::cout << b << '\n';
    return 0;
}
