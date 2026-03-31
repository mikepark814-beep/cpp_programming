#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> values(n);
    for (int& value : values) {
        std::cin >> value;
    }

    int remove_index;
    std::cin >> remove_index;

    int remove_value;
    std::cin >> remove_value;

    if(remove_index < 0 || remove_index >= n) {
        std::cerr << "Error: remove_index is out of bounds." << std::endl;
        return 1;
    }

    values.erase(values.begin() + remove_index);

    std::erase(values, remove_value);

    std::cout << values.size() << std::endl;
    for(int value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}
