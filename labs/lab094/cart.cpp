#include "cart.h"
#include <vector>
#include <algorithm>

static std::vector<std::pair<std::string, int>> cart;

void add_item(const std::string& name, int price) {
    cart.push_back({name, price});
}

bool has_item(const std::string& name) {
    for (const auto& [n, p] : cart) {
        if (n == name) return true;
    }
    return false;
}

void remove_item(const std::string& name) {
    auto it = std::find_if(cart.begin(), cart.end(),
        [&](const auto& p) { return p.first == name; });
    if (it != cart.end()) cart.erase(it);
}

int total_price() {
    int sum = 0;
    for (const auto& [n, p] : cart) sum += p;
    return sum;
}