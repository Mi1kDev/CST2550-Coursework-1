#include "classes.h"
#include <string>

// Method references for Person class
std::string Person::getName(){
  return name;
}
void Person::setName(std::string name){
  this->name = name;
}
std::string Person::getEmail(){
  return email;
}
void Person::setEmail(std::string email){
  this->email = email;
}
std::string Person::getAddress(){
  return address;
}
void Person::setAddress(std::string address){
  this->address = address;
}

// Method references for Librarian class

Librarian::Librarian(int staffId, std::string name, std::string address, std::string email, int salary){
  this->setStaffId(staffId);
  this->setName(name);
  this->setAddress(address);
  this->setEmail(email);
  this->setSalary(salary);
}
void Librarian::addMember(){

}
void Librarian::issueBook(int memberId, int bookId){

}
void Librarian::returnBook(int memberId, int bookId){

}
void Librarian::displayBorrowedBooks(int memberId){

}
void Librarian::calcFine(int memberId){

}
int Librarian::getStaffId(){
  return staffId;
}
void Librarian::setStaffId(int staffId){
  this->staffId = staffId;
}
int Librarian::getSalary(){
  return salary;
}
void Librarian::setSalary(int salary){
  this->salary = salary;
}

// Method references for Member class

Member::Member(int memberId, std::string name, std::string address, std::string email){
  this->memberId = memberId;
  this->setName(name);
  this->setAddress(address);
  this->setEmail(email);
}
std::string Member::getMemberId(){
  return std::to_string(memberId);
}
std::vector<Book> Member::getBooksBorrowed(){
  return booksLoaned;
}
void Member::setBooksBorrowed(Book book){

}

// Method references for Book class

Book::Book(int bookId, std::string bookName, std::string authorFirstName, std::string authorLastName){
  this->bookId = bookId;
  this->bookName = bookName;
  this->authorFirstName = authorFirstName;
  this->authorLastName = authorLastName;
}
std::string Book::getBookId(){
  return std::to_string(bookId);
}
std::string Book::getBookName(){
  return bookName;
}
std::string Book::getAuthorFirstName(){
  return authorFirstName;
}
std::string Book::getAuthorLastName(){
  return authorLastName;
}
Date Book::getDueDate(){
  return dueDate;
}
void Book::setDueDate(Date dueDate){
  this->dueDate = dueDate;
}
void Book::returnBook(){

}
void Book::borrowBook(Member* borrower, Date dueDate){

}
