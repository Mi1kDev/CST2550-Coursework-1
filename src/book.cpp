/*
book.cpp
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include "book.h"

/*
  Constructor for the Book class.
  @param bookId the provided id number of the book
  @param bookName the title of the book
  @param authorFirstName the author of the book's first name
  @param authorLastName the author of the book's last name
  @return instance of Book class
*/
Book::Book(int bookId, std::string bookName, std::string authorFirstName, std::string authorLastName){
  this->bookId = bookId;
  this->bookName = bookName;
  this->authorFirstName = authorFirstName;
  this->authorLastName = authorLastName;
}

/*
  Returns the Book's bookId property
  @return the Book's id number in the form of a string
*/
std::string Book::getBookId(){
  return std::to_string(bookId);
}

/*
  Returns the Book's bookName property
  @return the Book's title
*/
std::string Book::getBookName(){
  return bookName;
}

/*
  Return the Book's authorFirstName property
  @return the Book's author's first name
*/
std::string Book::getAuthorFirstName(){
  return authorFirstName;
}

/*
  Return the Book's authorLastName property
  @return the Book's author's last name
*/
std::string Book::getAuthorLastName(){
  return authorLastName;
}

/*
  Return the Book's dueDate property
  @return the date the Book is supposed to be returned by
*/
Date Book::getDueDate(){
  return dueDate;
}

/*
  Sets the Book's due date property to the value of the provided argument
  @param dueDate the date the Book should be returned by
*/
void Book::setDueDate(Date dueDate){
  this->dueDate = dueDate;
}

/*
  Sets the Book as being returned, meaning it is no longer borrowed by any Member
*/
void Book::returnBook(){
  // Sets the borrower property to be null as there is no longer anyone borrowing the book. Then prints out the date the book was returned at
  this->borrower = nullptr;
  std::time_t currentTime = std::time(0);
  std::tm* now = std::localtime(&currentTime);
  Date currentDate;
  currentDate.year = (now->tm_year + 1900);
  currentDate.month = (now->tm_mon + 1);
  currentDate.day = (now->tm_mday);
  std::cout << this->getBookName() << " returned on (dd-mm-yyyy): " << currentDate.day << "-" << currentDate.month << "-" << currentDate.year << std::endl;
}

/*
  Sets the Book as being borrowed by a Member as well as setting the date the Book needs to be returned by
  @param borrower a reference to the Member class who is currently borrowing the book
  @param dueDate the date by which the Book needs to be returned by without incurring fines
*/
void Book::borrowBook(Member* borrower, Date dueDate){
  this->borrower = borrower;
  this->setDueDate(dueDate);
}
