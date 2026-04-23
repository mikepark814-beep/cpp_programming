#include "Money.h"
#include <iostream>

int main() {
    Money a(10000, Currency::KRW);
    Money b(5, Currency::USD);        // 7000 KRW 상당

    std::cout << a.add(b).print();    // 17000.00 KRW
    std::cout << b.add(a).print();    // 12.14 USD 정도

    Money c(3000);                     // 기본값: KRW
    std::cout << c.print();            // 3000.00 KRW

    return 0;
}
