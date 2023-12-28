#include  <iostream>
#include <vector>
#ifndef _CLASSES_H
#define _CLASSES_H
class Person{
  private:
    std::string name;
    std::string email;
    std::string address;
  public:
    std::string getName();
    void setName(std::string name);
    std::string getAddress();
    void setAddress(std::string address);
    std::string getEmail();
    void setEmail(std::string email);
};
class Member;
class Librarian : public Person{
  private:
    int staffId;
    int salary;
  public:
    Librarian(int staffId, std::string name, std::string address, std::string email, int salary);
    // Edited from UML
    void addMember(std::vector<Member *> *memberList);
    void issueBook(int memberId, int bookId);
    void returnBook(int memberId, int bookId);
    void displayBorrowedBooks(int memberId);
    void calcFine(int memberId);
    int getStaffId();
    void setStaffId(int staffId);
    int getSalary();
    void setSalary(int salary);

};

struct Date{
  int day;
  int month;
  int year;
};

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
