#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values(n);

    for(int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }

    // sort(vlaues) << c++ 23 부터는 이렇게도 가능하다.
    std::sort(values.begin() , values.end());
    for(int i =0; i < n; ++i) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
