#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <string>

enum class Scale {
    Celsius,
    Fahrenheit
};

class Temperature {
public:
    Temperature(double temp, Scale scale = Scale::Celsius);
    Temperature add(const Temperature& other) const;
    std::string print() const;

private:
    double temperature;
    Scale scale;

    double toCelsius() const;
    double toFahrenheit() const;
};

#endif // TEMPERATURE_H
