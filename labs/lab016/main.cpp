#include <iostream>
#include <memory>

void update(int* a, int* b);

int main() {
    std::unique_ptr<int> a = std::make_unique<int>();
    std::unique_ptr<int> b = std::make_unique<int>();

    std::cin >> *a >> *b;

    update(a.get(), b.get());

    std::cout << *a << " " << *b << std::endl;

    return 0;
}

void update(int* a, int* b) {
    int original_a = *a;
    *a = original_a + *b;
    *b = original_a - *b;
}
