#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }

    int even_sum = 0;
    int odd_sum = 0;

    for (int value : values) {
        if (value % 2 == 0) {
            even_sum += value;
        } else {
            odd_sum += value;
        }
    }

    std::cout << even_sum << '\n';
    std::cout << odd_sum << '\n';

    return 0;
}