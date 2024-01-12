/*
member.cpp
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include "member.h"

/*
  Constructor for the Member class
  @param memberId the id number of the member
  @param name the name of the member
  @param address the address of the member
  @param email the email of the member
  @return instance of Member class
*/
Member::Member(int memberId, std::string name, std::string address, std::string email){
  this->memberId = memberId;
  this->setName(name);
  this->setAddress(address);
  this->setEmail(email);
}

/*
  Returns the memberId property of the Member as a string
  @return memberId the id number of the Member
*/
std::string Member::getMemberId(){
  return std::to_string(memberId);
}

/*
  Returns the booksLoaned property of the Member
  @return booksLoaned the list of books the Member has on loan
*/
std::vector<Book> Member::getBooksBorrowed(){
  return booksLoaned;
}

/*
  Adds or removes from the list of books the Member has on loan
  @param book A book class that is either added to the list of books on loan or is deconstructed and used to remove a book
*/
void Member::setBooksBorrowed(Book book){
  // If the provided book argument is that of the terminatorBook (Book(id, "END", "END", "END"))
  if(book.getBookName() == "END" && book.getAuthorLastName() == "END" && book.getAuthorLastName() == "END"){
    // Finds the book to remove from the booksLoaned list and removes it
    for(int i = 0; i < this->booksLoaned.size(); i++){
      if(this->booksLoaned[i].getBookId() == book.getBookId()){
        this->booksLoaned.erase(this->booksLoaned.begin() + i);
        break;
      }
    }
  }else{
    // Otherwise the book is simply added to booksLoaned
    this->booksLoaned.push_back(book);
  }

}
