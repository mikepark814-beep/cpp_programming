#pragma once

#include "OutputDevice.h"

class Monitor : public OutputDevice {
public:
    Monitor() {
        // TODO: print "Monitor constructor"
        std::cout << "Monitor constructor\n";
    }

    ~Monitor() override {
        // TODO: print "Monitor destructor"
        std::cout << "Monitor destructor\n";
    }

    void out() const override {
        // TODO: print "Monitor rendering"
        std::cout << "Monitor rendering\n";
    }
};