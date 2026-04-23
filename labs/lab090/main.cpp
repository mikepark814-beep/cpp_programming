#include <iostream>

void sort_three(int& a, int& b, int& c);

int main() {
    int x, y, z;
    std::cin >> x >> y >> z;
    sort_three(x, y, z);
    std::cout << x << " " << y << " " << z << std::endl;
    return 0;
}
