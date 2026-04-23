#include "Library.hpp"
#include <iostream>

// Author
Author::Author(const std::string& name, int birthYear)
    : name(name), birthYear(birthYear) {}
const std::string& Author::getName() const { return name; }
int Author::getBirthYear() const { return birthYear; }

// Book
Book::Book(const std::string& title, std::shared_ptr<Author> author)
    : title(title), author(author) {}
const std::string& Book::getTitle() const { return title; }
std::shared_ptr<const Author> Book::getAuthor() const { return author; }

// Library
Library::Library(const std::string& name) : name(name) {}
void Library::addBook(const Book& book) { books.push_back(book); }

void Library::printCatalog() const {
    std::cout << "Library: " << name << "\n";
    std::cout << "Total Books: " << books.size() << "\n";
    std::cout << "\n";
    for (const auto& b : books) {
        std::cout << "Title: " << b.getTitle() << "\n";
        auto a = b.getAuthor();
        if (a) {
            std::cout << "Author: " << a->getName() << "\n";
            std::cout << "Born: " << a->getBirthYear() << "\n";
        } else {
            std::cout << "Author: Unknown" << "\n";
            std::cout << "Born: N/A" << "\n";
        }
    }
}