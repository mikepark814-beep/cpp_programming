#include "stats.h"
#include <array>
#include <iostream>

int main() {
    std::array<int, N> a;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> a[i];
    }

    std::cout << "average: " << average(a) << '\n';
    std::cout << "range:   " << range(a)   << '\n';
    return 0;
}
