/*
classes.cpp
Author: M00829986
Created: 28/12/2024
Updated: 1/12/2024
*/
#include "classes.h"
#include <string>
#include <regex>
#include <vector>
#include <ctime>

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
void Librarian::addMember(std::vector<Member*>* memberList){
  std::cout << "[ Enter the information of the new member ]\n";

  std::string mName, mAddress, mEmail, opt;
  bool validated = false;
  bool nameValid = false, addressValid = false, emailValid = false;
  while(!validated){
    while(!nameValid){
      std::cout << "Enter Name: ";
      std::getline(std::cin, mName);
      if(mName.length() > 0){
        nameValid = true;
      }else{
        std::cout << "Name must contain at least a single character\n\n";
      }
    }
    while(!addressValid){
      std::cout << "Enter Address: ";
      std::getline(std::cin, mAddress);
      if(mAddress.length() > 0){
        addressValid = true;
      }else{
        std::cout << "Address must contain at least a single character\n\n";
      }
    }
    while(!emailValid){
      std::cout << "Enter Email: ";
      std::getline(std::cin, mEmail);

      //Pattern  might not fully  work
      std::regex emailPattern("[a-zA-Z0-9](.+)(@){1}[a-zA-Z0-9](.+)((.){1}[a-zA-Z](.+))(.+)");
      if(!regex_match(mEmail, emailPattern)){
        std::cout << "Invalid format for email\nReprompting...\n\n";
      }else{
        emailValid = true;
      }
    }
    std::cout << std::endl;
    std::cout << "The member's details are:\n";
    std::cout << "Name: " << mName << std::endl;
    std::cout << "Address: " << mAddress << std::endl;
    std::cout << "Email: " << mEmail << std::endl;

    bool optionSelected = false;
    while(!optionSelected){
      std::cout << "Are you sure this information is correct? [YES] or [NO]: ";
      std::getline(std::cin, opt);
      if(opt == "YES"){
        validated = true;
        optionSelected = true;
      }else if(opt == "NO"){
        std::cout << std::endl;
        optionSelected = true;
        nameValid = false;
        addressValid = false;
        emailValid = false;
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
void Librarian::issueBook(int memberId, int bookId, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  int foundMemberIdx, foundBookIdx;

  for(int i = 0; i < memberList->size(); i++){
    std::vector<Book> borrowedBooks = (*memberList)[i]->getBooksBorrowed();
    for(int j = 0; j < borrowedBooks.size(); j++){
      if(stoi(borrowedBooks[j].getBookId()) == bookId){
        std::cout << "This book is already on loan.\n";
        return;
      }
    }
  }
  for(int i = 0; i < memberList->size(); i++){
    if(memberId == stoi((*memberList)[i]->getMemberId())){
      foundMemberIdx = i;
      break;
    }
  }
  for(int i = 0; i < bookList->size(); i++){
    if(bookId == stoi((*bookList)[i]->getBookId())){
      foundBookIdx = i;
      break;
    }
  }
  Book issuedBook = *(*bookList)[foundBookIdx];
  std::time_t currentTime = std::time(0);
  std::tm* now = std::localtime(&currentTime);
  Date issueDate, dueDate;
  const int DAY_IN_SECONDS = 86400;
  const int DUE_LIMIT = -40;
  issueDate.year = (now->tm_year + 1900);
  issueDate.month = (now->tm_mon + 1);
  issueDate.day = (now->tm_mday);
  issueDate.timestamp = currentTime;
  std::time_t dueTime = currentTime + (DAY_IN_SECONDS * DUE_LIMIT);
  std::tm* due = std::localtime(&dueTime);
  dueDate.year = (due->tm_year + 1900);
  dueDate.month = (due->tm_mon + 1);
  dueDate.day = (due->tm_mday);
  dueDate.timestamp = dueTime;
  issuedBook.borrowBook((*memberList)[foundMemberIdx], dueDate);
  (*memberList)[foundMemberIdx]->setBooksBorrowed(issuedBook);

  std::cout << "[Book Details]" << std::endl;
  std::cout << "ID#: " << issuedBook.getBookId() << std::endl;
  std::cout << "NAME: " << issuedBook.getBookName() << std::endl;
  std::cout << "AUTHOR: " << issuedBook.getAuthorFirstName() << " " << issuedBook.getAuthorLastName() << std::endl;
  std::cout << std::endl;

  std::cout << "Book ID#: " << issuedBook.getBookId() << ", issued to Member ID#: " << memberId <<
  " on the Date (dd-mm-yyyy): " << issueDate.day << "-" << issueDate.month << "-" << issueDate.year
  << std::endl << "Due by (dd-mm-yyyy): " << dueDate.day << "-" << dueDate.month << "-" << dueDate.year;
  std::cout << std::endl;
}
void Librarian::returnBook(int memberId, int bookId, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  int foundBookIdx, foundMemberIdx;

  for(int i = 0; i < memberList->size(); i++){
    if(memberId == stoi((*memberList)[i]->getMemberId())){
      foundMemberIdx = i;
      break;
    }
  }
  for(int i = 0; i < bookList->size(); i++){
    if(bookId == stoi((*bookList)[i]->getBookId())){
      foundBookIdx = i;
      break;
    }
  }
  std::vector<Book> loanedBooks = (*memberList)[foundMemberIdx]->getBooksBorrowed();
  if(loanedBooks.size() <= 0){
    std::cout << "This member has no books out on loan" << std::endl;
    return;
  }
  for(int i = 0; i < loanedBooks.size(); i++){
    if(stoi(loanedBooks[i].getBookId()) == bookId){
      this->calcFine(memberId, memberList);
      (*bookList)[foundBookIdx]->returnBook();
      Book terminatorBook(bookId, "END", "END", "END");
      (*memberList)[foundMemberIdx]->setBooksBorrowed(terminatorBook);
      return;
    }
  }
  std::cout << "The member does not have the book with id#: " << bookId << " out on loan" << std::endl;


}
void Librarian::displayBorrowedBooks(int memberId, std::vector<Member*>* memberList){
  int memberIdx;
  std::cout << std::endl;
  for(int i = 0; i < memberList->size(); i++){
    if(std::to_string(memberId) == (*memberList)[i]->getMemberId()){
      memberIdx = i;
      break;
    }
  }

  std::cout << "NAME: " << (*memberList)[memberIdx]->getName() << std::endl;
  std::cout << "ADDRESS: " << (*memberList)[memberIdx]->getAddress() << std::endl;
  std::cout << "EMAIL: " << (*memberList)[memberIdx]->getEmail() << std::endl;

  std::vector<Book> loanedBooks = (*memberList)[memberIdx]->getBooksBorrowed();
  if(loanedBooks.size() <= 0){
    std::cout << "This member has not borrowed any books as of yet.\n";
  }
  for(int i = 0; i < loanedBooks.size(); i++){
    std::cout << "[Book " << (i+1) << "]" << std::endl;
    std::cout << "ID: " << loanedBooks[i].getBookId() << std::endl;
    std::cout << "BOOK NAME: " << loanedBooks[i].getBookName() << std::endl;
    std::cout << "AUTHOR NAME: " << loanedBooks[i].getAuthorFirstName() << " " << loanedBooks[i].getAuthorLastName() << std::endl;
    Date dueDate = loanedBooks[i].getDueDate();
    std::cout << "DUE DATE (dd-mm-yyyy): " << dueDate.day << "-" << dueDate.month << "-" << dueDate.year << std::endl;
    std::cout << std::endl;
  }

}
void Librarian::calcFine(int memberId, std::vector<Member*>* memberList){
  int foundIdx;
  std::cout << std::endl;

  for(int i = 0; i < memberList->size(); i++){
    if(std::to_string(memberId) == (*memberList)[i]->getMemberId()){
      foundIdx = i;
      break;
    }
  }

  std::vector<Book> loanedBooks = (*memberList)[foundIdx]->getBooksBorrowed();
  if(loanedBooks.size() <= 0){
    std::cout << "This member has no books on loan at the moment\n";
    return;
  }
  int totalFines = 0;
  const int DAY_IN_SECONDS = 86400;
  std::time_t currentTime = std::time(0);
  if(loanedBooks.size() > 0){
    std::cout << "[Overdue Books]" << std::endl;
    for(int i = 0; i < loanedBooks.size(); i++){
        std::time_t dueTime = loanedBooks[i].getDueDate().timestamp;
        double timeDiff = std::difftime(currentTime, dueTime) / DAY_IN_SECONDS;
        if(timeDiff > 0){
          std::cout << "BOOK ID#: " << loanedBooks[i].getBookId() << std::endl;
          std::cout << "BOOK NAME: " << loanedBooks[i].getBookName() << std::endl;
          std::cout << "OVERDUE BY: " << (int)timeDiff << " days" << std::endl;
          int fines = 1 * (int)timeDiff;
          std::cout << "FINES INCURRED: £" << fines << std::endl;
          totalFines += fines;
          std::cout << std::endl;
        }
    }
  }
  if(totalFines == 0){
    std::cout << "No calculated fines as there are no overdue and outstanding books\n";
  }else{
    std::cout << "TOTAL FINES: £" << totalFines << std::endl;
  }


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
  if(book.getBookName() == "END" && book.getAuthorLastName() == "END" && book.getAuthorLastName() == "END"){
    for(int i = 0; i < this->booksLoaned.size(); i++){
      if(this->booksLoaned[i].getBookId() == book.getBookId()){
        this->booksLoaned.erase(this->booksLoaned.begin() + i);
        break;
      }
    }
  }else{
    this->booksLoaned.push_back(book);
  }

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
  this->borrower = nullptr;
  std::time_t currentTime = std::time(0);
  std::tm* now = std::localtime(&currentTime);
  Date currentDate;
  currentDate.year = (now->tm_year + 1900);
  currentDate.month = (now->tm_mon + 1);
  currentDate.day = (now->tm_mday);
  std::cout << this->getBookName() << " returned on (dd-mm-yyyy): " << currentDate.day << "-" << currentDate.month << "-" << currentDate.year << std::endl;
}
void Book::borrowBook(Member* borrower, Date dueDate){
  this->borrower = borrower;
  this->setDueDate(dueDate);
}
