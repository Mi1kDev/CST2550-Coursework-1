#include "classes.h"
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
