#pragma once

#include <iostream>

class OutputDevice {
public:
    OutputDevice() {
        // TODO: print "OutputDevice constructor"
        std::cout << "OutputDevice constructor\n";
    }

    virtual ~OutputDevice() {
        // TODO: print "OutputDevice destructor"
        std::cout << "OutputDevice destructor\n";
    }

    virtual void out() const = 0;
};