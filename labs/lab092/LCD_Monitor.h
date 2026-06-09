#pragma once
#include "Monitor.h"

// TODO: LCD_Monitor 클래스를 구현하세요 (Monitor를 public 상속).
// 생성자: "LCD_Monitor constructor" 출력
// 소멸자: override, "LCD_Monitor destructor" 출력
class LCD_Monitor : public Monitor {
public:
    LCD_Monitor() { std::cout << "LCD_Monitor constructor\n"; }
    ~LCD_Monitor() override { std::cout << "LCD_Monitor destructor\n"; }
};
