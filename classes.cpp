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
void Librarian::issueBook(int memberId, int bookId, std::vector<Member *> *memberList, std::vector<Book *> *bookList){
  int foundMemberIdx, foundBookIdx;
  if(memberList->size() <= 0){
    std::cout << "No members available to issue books to.\n";
    return;
  }
  if(bookList->size() <= 0){
    std::cout << "No books availableto be issued.\n";
    return;
  }
  for(int i = 0; i < memberList->size(); i++){
    std::vector<Book> borrowedBooks = (*memberList)[i]->getBooksBorrowed();
    for(int j = 0; j < borrowedBooks.size(); j++){
      if(stoi(borrowedBooks[j].getBookId()) == bookId){
        std::cout << "This book is already on loan to someone else.\n";
        return;
      }
    }
  }
  for(int i = 0; i < memberList->size(); i++){
    if(memberId == stoi((*memberList)[i]->getMemberId())){
      foundMemberIdx = i;
      break;
    }
    if(i == memberList->size() - 1){
      std::cout << "The provided member id {"<< memberId <<"} is not present.\n";
      return;
    }
  }
  for(int i = 0; i < bookList->size(); i++){
    if(bookId == stoi((*bookList)[i]->getBookId())){
      foundBookIdx = i;
      break;
    }
    if(i == bookList->size() - 1){
      std::cout << "The provided book id {"<< bookId << "} is not present.\n";
      return;
    }
  }
  Book issuedBook = *(*bookList)[foundBookIdx];
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  Date issueDate, dueDate;
  int month[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  issueDate.year = (now->tm_year + 1900);
  issueDate.month = (now->tm_mon + 1);
  issueDate.day = (now->tm_mday);
  dueDate.day = issueDate.day + 3;
  dueDate.year = issueDate.year;
  dueDate.month = issueDate.month;
  if(dueDate.day > month[issueDate.month - 1]){
    dueDate.day = dueDate.day % month[issueDate.month - 1];
    dueDate.month++;
    if(dueDate.month > 12){
      dueDate.month = dueDate.month % 12;
      dueDate.year++;
    }
  }
  issuedBook.borrowBook((*memberList)[foundMemberIdx], dueDate);
  (*memberList)[foundMemberIdx]->setBooksBorrowed(issuedBook);

  std::cout << "Book ID#: " << issuedBook.getBookId() << ", issued to Member ID#: " << memberId <<
  " on the Date (dd-mm-yyyy): " << issueDate.day << "-" << issueDate.month << "-" << issueDate.year
  << std::endl << "Due by (dd-mm-yyyy): " << dueDate.day << "-" << dueDate.month << "-" << dueDate.year;
  std::cout << std::endl;
}
void Librarian::returnBook(int memberId, int bookId){

}
void Librarian::displayBorrowedBooks(int memberId, std::vector<Member *> *memberList){
  int memberIdx;
  for(int i = 0; i < memberList->size(); i++){
    if(std::to_string(memberId) == (*memberList)[i]->getMemberId()){
      memberIdx = i;
      break;
    }
    if(i == memberList->size() - 1){
      std::cout <<  "The provided member id {" << memberId << "} does not exist.";
      return;
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
    std::cout << "BOOK NAME: " << loanedBooks[i].getBookName() << std::endl;
    std::cout << "AUTHOR NAME: " << loanedBooks[i].getAuthorFirstName() << " " << loanedBooks[i].getAuthorLastName() << std::endl;
    Date dueDate = loanedBooks[i].getDueDate();
    std::cout << "DUE DATE (dd-mm-yyyy): " << dueDate.day << "-" << dueDate.month << "-" << dueDate.year << std::endl;
  }

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
  this->borrower = borrower;
  this->setDueDate(dueDate);
}
