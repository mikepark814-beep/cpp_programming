#include <iostream>

enum class TrafficLight {
    Red = 0,
    Yellow = 1,
    Green = 2
};

int main() {
    int code;
    std::cin >> code;

    const auto light = static_cast<TrafficLight>(code);

    switch (light) {
        case TrafficLight::Red:
            std::cout << "STOP";
            break;
        case TrafficLight::Yellow:
            std::cout << "READY";
            break;
        case TrafficLight::Green:
            std::cout << "GO";
            break;
        default:
            std::cout << "UNKNOWN";
            break;
    }

    return 0;
}