#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <memory>
#include <vector>

class Author {
public:
    Author(const std::string& name, int birthYear);
    const std::string& getName() const;
    int getBirthYear() const;
private:
    std::string name;
    int birthYear;
};

class Book {
public:
    // author는 nullptr 가능 (익명 저자)
    Book(const std::string& title,
         std::shared_ptr<Author> author = nullptr);
    const std::string& getTitle() const;
    std::shared_ptr<const Author> getAuthor() const;   // const 반환!
private:
    std::string title;
    std::shared_ptr<Author> author;
};

class Library {
public:
    explicit Library(const std::string& name);
    void addBook(const Book& book);
    void printCatalog() const;
private:
    std::string name;
    std::vector<Book> books;
};

#endif // LIBRARY_HPP
