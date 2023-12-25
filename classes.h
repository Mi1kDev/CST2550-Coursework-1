#include  <iostream>
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

class Librarian : public Person{
  private:
    int staffId;
    int salary;
  public:
    Librarian(int staffId, std::string name, std::string address, std::string email, int salary);
    void addMember();
    void issueBook(int memberId, int bookId);
    void returnBook(int memberId, int bookId);
    void displayBorrowedBooks(int memberId);
    void calcFine(int memberId);
    int getStaffId();
    void setStaffId(int staffId);
    int getSalary();
    void setSalary(int salary);

};
#endif
