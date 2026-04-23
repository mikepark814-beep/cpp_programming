#ifndef NUMBERLIST_H
#define NUMBERLIST_H

#include <vector>

class NumberList {
private:
    std::vector<int> data_;

public:
    NumberList(const std::vector<int>& init);

    // 체이닝 가능 연산 (*this 반환)
    NumberList& addAll(int x);                  // 모든 원소에 x를 더함
    NumberList& multiplyAll(int x);             // 모든 원소에 x를 곱함
    NumberList& removeIf(bool (*pred)(int));    // pred가 true인 원소 제거

    // 터미널 연산 (const)
    int sum() const;
    std::vector<int> toVector() const;
};

#endif // NUMBERLIST_H
