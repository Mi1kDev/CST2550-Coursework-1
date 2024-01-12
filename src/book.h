#ifndef BOOK_H
#define BOOK_H
/*
book.h
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include "member.h"
#include "date.h"

// Class forwarding of member class to allow for compilation
class Member;
// Implementation of the Book class, its properties and methods
class Book{
  private:
    int bookId;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    Member* borrower;
  public:
    Book(int bookId, std::string bookName, std::string authorFirstName, std::string authorLastName);
    std::string getBookId();
    std::string getBookName();
    std::string getAuthorFirstName();
    std::string getAuthorLastName();
    Date getDueDate();
    void setDueDate(Date dueDate);
    void returnBook();
    void borrowBook(Member* borrower, Date dueDate);
};
#endif
