#include "stats.h"
#include <algorithm>
#include <numeric>

double average(const std::array<int, N>& arr) {
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    return static_cast<double>(sum) / N;
}

int range(const std::array<int, N>& arr) {
    auto mn = std::min_element(arr.begin(), arr.end());
    auto mx = std::max_element(arr.begin(), arr.end());
    return *mx - *mn;
}