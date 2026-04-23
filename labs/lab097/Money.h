#ifndef MONEY_H
#define MONEY_H

#include <string>

enum class Currency {
    KRW,  // 원
    USD   // 달러 (1 USD = 1400 KRW 고정)
};

class Money {
public:
    // amount의 단위는 주어진 currency 기준
    Money(double amount, Currency currency = Currency::KRW);

    // 두 Money 값을 더한 새 Money 반환. 결과의 통화는 *this 의 통화.
    Money add(const Money& other) const;

    // "12345.67 KRW\n" 또는 "8.75 USD\n" 형식 (소수점 2자리)
    std::string print() const;

private:
    double amount;
    Currency currency;

    double toKRW() const;
    double toUSD() const;
};

#endif // MONEY_H
