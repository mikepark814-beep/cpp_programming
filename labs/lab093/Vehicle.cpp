#include "Vehicle.hpp"

// TODO: make_vehicle() 함수를 구현하세요.
// 매개변수 choice("gv70", "grandeur", "carnival") 값에 따라
// 해당 Vehicle 파생 클래스의 unique_ptr을 반환합니다.
std::unique_ptr<Vehicle> make_vehicle(const std::string& choice) {
    // TODO: 분기 처리
    if (choice == "gv70")     return std::make_unique<GV70>();
    if (choice == "grandeur") return std::make_unique<Grandeur>();
    if (choice == "carnival") return std::make_unique<Carnival>();
    return nullptr;
}

void GV70::accelerate() {
    // TODO: "The speed of the gv70 has increased by 30 km/h." 출력
    std::cout << "The speed of the gv70 has increased by 30 km/h." << std::endl;
}

void Grandeur::accelerate() {
    // TODO: "The speed of the grandeur has increased by 20 km/h." 출력
    std::cout << "The speed of the grandeur has increased by 20 km/h." << std::endl;
}

void Carnival::accelerate() {
    // TODO: "The speed of the carnival has increased by 10 km/h." 출력
    std::cout << "The speed of the carnival has increased by 10 km/h." << std::endl;
}
