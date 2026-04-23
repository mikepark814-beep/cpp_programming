#include "NumberList.h"
#include <iostream>

bool is_even(int x) { return x % 2 == 0; }

int main() {
    NumberList nl({1, 2, 3, 4, 5});

    // 체이닝: {1..5} -> addAll(10) -> {11..15}
    //               -> removeIf(is_even) -> {11,13,15}
    //               -> multiplyAll(2) -> {22,26,30}
    //               -> sum() -> 78
    int result = nl.addAll(10)
                   .removeIf(is_even)
                   .multiplyAll(2)
                   .sum();

    std::cout << "sum = " << result << '\n';   // 78

    for (int v : nl.toVector()) std::cout << v << ' ';
    std::cout << '\n';                          // 22 26 30

    return 0;
}
