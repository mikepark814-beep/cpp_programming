#include <iomanip>
#include <iostream>

int main() {
    const int baseGold = 1000;
    int minionGold = 0;
    std::cin >> minionGold;
    // calculate totalGold and averageGold, then print the final status based on totalGold >= 4000

    int totalGold = baseGold + minionGold;
    auto averageGold = (baseGold + minionGold) / 2;
    

    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "Total Gold: " << totalGold << std::endl;
    std::cout << "Average Gold: " << averageGold << std::endl;
    if(totalGold >= 4000) {
        std::cout << "Item Purchase Available" << std::endl;
    }
    
    else {
        std::cout << "More Gold Needed" << std::endl;
    }
    
    return 0;
}