#include "classes.h"
#include <string>
#include <regex>
#include <vector>

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
// Edited from UML
void Librarian::addMember(std::vector<Member *> *memberList){
  std::cout << "[ Enter the information of the new member ]\n";

  std::string mName, mAddress, mEmail, opt;
  bool validated = false;
  while(!validated){
    while(true){
      std::cout << "Enter Name: ";
      std::getline(std::cin, mName);
      if(mName.length() > 0){
        break;
      }else{
        std::cout << "Name must contain at least a single character\n\n";
      }
    }
    while(true){
      std::cout << "Enter Address: ";
      std::getline(std::cin, mAddress);
      if(mAddress.length() > 0){
        break;
      }else{
        std::cout << "Address must contain at least a single character\n\n";
      }
    }

    while(true){
      std::cout << "Enter Email: ";
      std::getline(std::cin, mEmail);

      //Pattern  might not fully  work
      std::regex emailPattern("[a-zA-Z0-9](.+)(@){1}[a-zA-Z0-9](.+)((.){1}[a-zA-Z](.+))(.+)");
      if(!regex_match(mEmail, emailPattern)){
        std::cout << "Invalid format for email\nReprompting...\n\n";
      }else{
        break;
      }
    }
    std::cout << std::endl;
    std::cout << "The member's details are:\n";
    std::cout << "Name: " << mName << std::endl;
    std::cout << "Address: " << mAddress << std::endl;
    std::cout << "Email: " << mEmail << std::endl;

    while(true){
      std::cout << "Are you sure this information is correct? [YES] or [NO]: ";
      std::getline(std::cin, opt);
      if(opt == "YES"){
        validated = true;
        break;
      }else if(opt == "NO"){
        std::cout << std::endl;
        break;
      }else{
        std::cout << "Invalid option selected. Either check that your input is spelt correctly or provide the correct input.\n\n";
      }
    }
  }
  int mId;
  mId = memberList->size();
  std::cout << std::endl;
  std::cout << "[ Member Details ]\n";
  std::cout << "ID #: " << mId << std::endl;
  std::cout << "NAME: " << mName << std::endl;
  std::cout << "ADDRESS: " << mAddress << std::endl;
  std::cout << "EMAIL: " << mEmail << std::endl;
  Member * member = new Member(mId, mName, mAddress, mEmail);
  memberList->push_back(member);
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
  this->booksLoaned.push_back(book);
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
