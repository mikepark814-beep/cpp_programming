#include "normalize.h"
#include <iostream>

int main() {
    std::cout << "[" << normalize("  Hello, World!!  ") << "]\n";  // [hello world]
    std::cout << "[" << normalize("...A.B.C...")        << "]\n";  // [abc]
    std::cout << "[" << normalize("   ")                << "]\n";  // []
    std::cout << "[" << normalize("C++ is Fun!!")        << "]\n";  // [c is fun]
    return 0;
}
