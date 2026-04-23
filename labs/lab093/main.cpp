#include "runner.h"
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    std::vector<Runner> v(n);
    for (auto& r : v) {
        std::cin >> r.name >> r.minutes >> r.age;
    }

    rank_runners(v);

    for (const auto& r : v) {
        std::cout << r.name << '\n';
    }
    return 0;
}
