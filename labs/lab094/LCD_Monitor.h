#pragma once

#include "Monitor.h"

class LCD_Monitor : public Monitor {
public:
    LCD_Monitor() {
        // TODO: print "LCD_Monitor constructor"
        std::cout << "LCD_Monitor constructor\n";
    }

    ~LCD_Monitor() override {
        // TODO: print "LCD_Monitor destructor"
        std::cout << "LCD_Monitor destructor\n";
    }

    void out() const override {
        // TODO: print "LCD_Monitor rendering"
        std::cout << "LCD_Monitor rendering\n";
    }
};