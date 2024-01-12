#ifndef LIBRARIAN_H
#define LIBRARIAN_H
/*
librarian.h
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include <regex>
#include "person.h"
#include "member.h"
#include "book.h"

// Implementation of Librarian class, its properties and methods
class Librarian : public Person{
  private:
    int staffId;
    int salary;
  public:
    Librarian(int staffId, std::string name, std::string address, std::string email, int salary);
    // Edited from UML
    void addMember(std::vector<Member*>* memberList);
    void issueBook(int memberId, int bookId, std::vector<Member*>* memberList, std::vector<Book*>* bookList);
    void returnBook(int memberId, int bookId, std::vector<Member*>* memberList, std::vector<Book*>* bookList);
    void displayBorrowedBooks(int memberId, std::vector<Member*>* memberList);
    void calcFine(int memberId, std::vector<Member*>* memberList);
    int getStaffId();
    void setStaffId(int staffId);
    int getSalary();
    void setSalary(int salary);

};
#endif
