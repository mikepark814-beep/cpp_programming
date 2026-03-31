#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int* arr = nullptr;
    arr = new int[n];
    
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int index;
    std::cin >> index;
    std::cout << arr[arr[index]] << std::endl;
    
    delete[] arr;

    return 0;
}
