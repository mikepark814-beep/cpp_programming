#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::map<std::string, int> count_words(const std::vector<std::string>& words) {
    std::map<std::string, int> m;
    for (const auto& w : words) m[w]++;
    return m;
}

void print_top(const std::map<std::string, int>& freq, int k) {
    std::vector<std::pair<std::string, int>> v(freq.begin(), freq.end());
    std::sort(v.begin(), v.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    int limit = std::min(k, (int)v.size());
    for (int i = 0; i < limit; ++i) {
        std::cout << v[i].first << " " << v[i].second << "\n";
    }
}