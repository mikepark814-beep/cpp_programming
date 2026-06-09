#pragma once

#include "Monitor.h"

class LED_Monitor : public Monitor {
public:
    LED_Monitor() {
        // TODO: print "LED_Monitor constructor"
        std::cout << "LED_Monitor constructor\n";
    }

    ~LED_Monitor() override {
        // TODO: print "LED_Monitor destructor"
        std::cout << "LED_Monitor destructor\n";
    }

    void out() const override {
        // TODO: print "LED_Monitor rendering"
        std::cout << "LED_Monitor rendering\n";
    }
};