#include "Temperature.h"
#include <sstream>
#include <iomanip>

// TODO: 아래 다섯 함수를 구현하세요.
// Temperature 객체는 생성 후 상태가 변하지 않습니다 (불변 객체).
// add 함수는 새 Temperature 객체를 반환해야 합니다.

Temperature::Temperature(double temp, Scale scale) 
    : temperature(temp), scale(scale) {
            // 힌트: 멤버 초기화 리스트를 사용하세요.
            //       : temperature(temp), scale(scale)
    }


double Temperature::toCelsius() const {
    // 이미 Celsius이면 그대로 반환합니다.
    // Fahrenheit이면 (temperature - 32) * 5.0 / 9.0 으로 변환합니다.
    if (scale == Scale::Celsius) {
        return temperature;}
    else {
        return (temperature - 32) * 5.0 / 9.0;
    }
}

double Temperature::toFahrenheit() const {
    // 이미 Fahrenheit이면 그대로 반환합니다.
    // Celsius이면 temperature * 9.0 / 5.0 + 32 로 변환합니다.
    if (scale == Scale::Fahrenheit) {
        return temperature;
    }
    else {
        return temperature * 9.0 / 5.0 + 32;
    }
}

Temperature Temperature::add(const Temperature& other) const {
    // 호출자의 scale에 맞춰 결과를 반환합니다.
    // 예: this가 Celsius이면 other를 Celsius로 변환 후 더합니다.
    // 힌트: toCelsius() / toFahrenheit() 를 활용하세요.
    // 주의: *this 와 other 를 수정하면 안 됩니다 (const).
    if (scale == Scale::Celsius) {
        double otherInCelsius = other.toCelsius();
        double result = temperature + otherInCelsius;
        return Temperature(result, Scale::Celsius);
    }
    else {
        double otherInFahrenheit = other.toFahrenheit();
        double result = temperature + otherInFahrenheit;
        return Temperature(result, Scale::Fahrenheit);
    }
}

std::string Temperature::print() const {
    // "25.0 C\n" 또는 "77.0 F\n" 형식으로 반환합니다.
    // 힌트: std::ostringstream + std::fixed + std::setprecision(1)
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    if (scale == Scale::Celsius) {
        oss << temperature << " C\n";
    }
    else {
        oss << temperature << " F\n";
    }

    return oss.str();
}