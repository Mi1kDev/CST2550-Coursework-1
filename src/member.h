#ifndef MEMBER_H
#define MEMBER_H
/*
member.h
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include <vector>
#include "person.h"
#include "book.h"

// class forwarding done to accommodate compilation
class Book;
// Implementation of member class, its properties and methods
class Member : public Person{
  private:
    int memberId;
    std::vector<Book> booksLoaned;
  public:
    Member(int memberId, std::string name, std::string address, std::string email);
    std::string getMemberId();
    std::vector<Book> getBooksBorrowed();
    void setBooksBorrowed(Book book);
};
#endif
