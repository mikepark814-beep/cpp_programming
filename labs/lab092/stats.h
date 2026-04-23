#ifndef STATS_H
#define STATS_H

#include <array>
#include <cstddef>

constexpr size_t N = 5;

// 평균을 double로 반환
double average(const std::array<int, N>& arr);

// 최댓값 - 최솟값
int range(const std::array<int, N>& arr);

#endif // STATS_H
