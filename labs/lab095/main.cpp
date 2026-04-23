#include "wordfreq.h"
#include <iostream>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::string> ws(n);
    for (auto& w : ws) std::cin >> w;

    auto freq = count_words(ws);
    print_top(freq, k);
    return 0;
}
