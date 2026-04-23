#include "NumberList.h"
#include <algorithm>

NumberList::NumberList(const std::vector<int>& init) : data_(init) {}

NumberList& NumberList::addAll(int x) {
    for (auto& v : data_) v += x;
    return *this;
}

NumberList& NumberList::multiplyAll(int x) {
    for (auto& v : data_) v *= x;
    return *this;
}

NumberList& NumberList::removeIf(bool (*pred)(int)) {
    std::erase_if(data_, pred);
    return *this;
}

int NumberList::sum() const {
    int s = 0;
    for (int v : data_) s += v;
    return s;
}

std::vector<int> NumberList::toVector() const {
    return data_;
}