#include "Library.hpp"
#include <iostream>

int main() {
    auto tolkien = std::make_shared<Author>("J.R.R. Tolkien", 1892);

    Library lib("Main Library");
    lib.addBook(Book("The Hobbit", tolkien));
    lib.addBook(Book("Beowulf"));   // 익명 저자

    lib.printCatalog();

    return 0;
}
