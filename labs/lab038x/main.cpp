#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values;
    values.reserve(n);

    // n개의 정수 입력
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(values));

    // 정렬
    std::sort(values.begin(), values.end());

    // 한 줄에 하나씩 출력
    std::copy(values.begin(), values.end(), std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}