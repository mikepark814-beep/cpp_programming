#include <iostream>
#include <memory>

#include "LCD_Monitor.h"
#include "LED_Monitor.h"

int main() {
    {
        Monitor monitor;
        monitor.out();
    }

    std::cout << "--------------------------\n";

    {
        Monitor* monitor = new LED_Monitor();
        monitor->out();
        delete monitor;
    }

    std::cout << "--------------------------\n";

    {
        std::unique_ptr<OutputDevice> monitor = std::make_unique<LCD_Monitor>();
        monitor->out();
    }
}