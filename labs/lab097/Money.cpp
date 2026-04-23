#include "Money.h"
#include <sstream>
#include <iomanip>

constexpr double USD_TO_KRW = 1400.0;

Money::Money(double amount, Currency currency)
    : amount(amount), currency(currency) {}

double Money::toKRW() const {
    if (currency == Currency::KRW) return amount;
    return amount * USD_TO_KRW;
}

double Money::toUSD() const {
    if (currency == Currency::USD) return amount;
    return amount / USD_TO_KRW;
}

Money Money::add(const Money& other) const {
    if (currency == Currency::KRW) {
        return Money(amount + other.toKRW(), Currency::KRW);
    } else {
        return Money(amount + other.toUSD(), Currency::USD);
    }
}

std::string Money::print() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount << " "
        << (currency == Currency::KRW ? "KRW" : "USD") << "\n";
    return oss.str();
}