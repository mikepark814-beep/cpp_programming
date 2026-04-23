#include "cart.h"
#include <iostream>

int main() {
    add_item("apple", 1000);
    add_item("milk", 2500);
    add_item("bread", 3000);

    std::cout << "has milk?   " << (has_item("milk")   ? "yes" : "no") << '\n';
    std::cout << "has cheese? " << (has_item("cheese") ? "yes" : "no") << '\n';
    std::cout << "total: " << total_price() << '\n';   // 6500

    remove_item("apple");
    remove_item("banana"); // 없어도 에러 X
    std::cout << "total after remove: " << total_price() << '\n';  // 5500

    return 0;
}
