/*
librarian.cpp
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include "librarian.h"

/*
  Constructor for Librarian class
  @param staffId the id number of the Librarian
  @param name the Librarian's name
  @param address the Librarian's address
  @param email the Librarian's email address
  @param salary the Librarian's current salary
  @return an instance of the Librarian class
*/
Librarian::Librarian(int staffId, std::string name, std::string address, std::string email, int salary){
  this->setStaffId(staffId);
  this->setName(name);
  this->setAddress(address);
  this->setEmail(email);
  this->setSalary(salary);
}

/*
  Allows for creation of new members and their addition to the list of existing members
  @param memberList pointer to a vector which stores members, the vector is a list of all existing members
*/
void Librarian::addMember(std::vector<Member*>* memberList){
  std::cout << "[ Enter the information of the new member ]\n";

  std::string mName, mAddress, mEmail, opt;
  std::regex namePattern("[a-zA-Z -]+");
  std::regex addressPattern("[a-zA-Z0-9 -]+");
  std::regex emailPattern("[a-zA-Z0-9](.+)(@){1}[a-zA-Z0-9](.+)((.){1}[a-zA-Z](.+))(.+)");
  bool validated = false;
  bool nameValid = false, addressValid = false, emailValid = false;

  // Asks for input from the user until the user confirms their information is valid
  while(!validated){
    // Ensures that the user enters at least a single character for a name
    while(!nameValid){
      std::cout << "Enter Name: ";
      std::getline(std::cin, mName);
      if(std::regex_match(mName, namePattern)){
        nameValid = true;
      }else{
        std::cout << "Name must consist of alphabetical characters\n\n";
      }
    }
    // Ensures that the user enters at least a single character for an address
    while(!addressValid){
      std::cout << "Enter Address: ";
      std::getline(std::cin, mAddress);
      if(std::regex_match(mAddress, addressPattern)){
        addressValid = true;
      }else{
        std::cout << "Address must consist of alphanumeric characters\n\n";
      }
    }
    // Ensures that the user enters an email matching the proper structure of an email address
    while(!emailValid){
      std::cout << "Enter Email: ";
      std::getline(std::cin, mEmail);
      if(!regex_match(mEmail, emailPattern)){
        std::cout << "Invalid format for email\n\n";
      }else{
        emailValid = true;
      }
    }
    // Displays user details so the user can determine if the information is correct
    std::cout << std::endl;
    std::cout << "The member's details are:\n";
    std::cout << "NAME: " << mName << std::endl;
    std::cout << "ADDRESS: " << mAddress << std::endl;
    std::cout << "EMAIL: " << mEmail << std::endl;
    std::cout << std::endl;
    bool optionSelected = false;
    // Asks the user for input until one of the provided options is selected
    while(!optionSelected){
      std::cout << "Are you sure this information is correct? [YES] or [NO]: ";
      std::getline(std::cin, opt);
      // Stops the loop as the user has confirmed their information is correct
      if(opt == "YES"){
        validated = true;
        optionSelected = true;
      // Reprompts the user for relevant information
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
  // the member id will be equal to the size of the memberList
  mId = memberList->size();
  // Prints member's details and stores it in the list of all members
  std::cout << std::endl;
  std::cout << "[ Member Details ]\n";
  std::cout << "ID #: " << mId << std::endl;
  std::cout << "NAME: " << mName << std::endl;
  std::cout << "ADDRESS: " << mAddress << std::endl;
  std::cout << "EMAIL: " << mEmail << std::endl;
  std::cout << std::endl;
  Member * member = new Member(mId, mName, mAddress, mEmail);
  memberList->push_back(member);
}

/*
  Issues a book with the provided bookId to a member with the provided memberId
  @param memberId Id number of the member to issue the book to
  @param bookId Id number of the book that is to be issued
  @param memberList reference to all members stored in the system
  @param bookList reference to all books stored in the system
*/
void Librarian::issueBook(int memberId, int bookId, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  int foundMemberIdx, foundBookIdx;

  // Determines whether the book with the specified bookId is on loan already
  for(int i = 0; i < memberList->size(); i++){
    std::vector<Book> borrowedBooks = (*memberList)[i]->getBooksBorrowed();
    for(int j = 0; j < borrowedBooks.size(); j++){
      if(stoi(borrowedBooks[j].getBookId()) == bookId){
        std::cout << "This book is already on loan.\n";
        return;
      }
    }
    // Finds the index in the memberList at which the member with the provided memberId is found
    if(memberId == stoi((*memberList)[i]->getMemberId())){
      foundMemberIdx = i;
    }
  }

  // Finds the index in the bookList at which the book with the provided bookId is found
  for(int i = 0; i < bookList->size(); i++){
    if(bookId == stoi((*bookList)[i]->getBookId())){
      foundBookIdx = i;
      break;
    }
  }

  // Calculates the dueDate of the book being issued
  Book issuedBook = *(*bookList)[foundBookIdx];
  std::time_t currentTime = std::time(0);
  std::tm* now = std::localtime(&currentTime);
  Date issueDate, dueDate;
  const int DAY_IN_SECONDS = 86400;
  const int DUE_LIMIT = 3;
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
  // Sets the Book's borrower to be the current member and its dueDate to be the calculated due date
  issuedBook.borrowBook((*memberList)[foundMemberIdx], dueDate);
  // Updates the Member's list of books on loan by passing the found Book object
  (*memberList)[foundMemberIdx]->setBooksBorrowed(issuedBook);

  // Displays Book's information
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

/*
  Returns the book that has the provided bookId that is out on loan by the member with the specified memberId
  @param memberId the id number of the member returning a book
  @param bookId the id number of the book being returned
  @param memberList a reference to the list of all members
  @param bookList a reference to the list of all books
*/
void Librarian::returnBook(int memberId, int bookId, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  int foundBookIdx, foundMemberIdx;

  // Finds the index at which the matching memberId is found inside the memberList
  for(int i = 0; i < memberList->size(); i++){
    if(memberId == stoi((*memberList)[i]->getMemberId())){
      foundMemberIdx = i;
      break;
    }
  }

  // Finds the index at which the matching bookId is found inside the bookList
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
  // If the Member has a book with the corresponding bookId on loan then fines are calculated for all overdue books and the book is returned
  for(int i = 0; i < loanedBooks.size(); i++){
    if(stoi(loanedBooks[i].getBookId()) == bookId){
      this->calcFine(memberId, memberList);
      (*bookList)[foundBookIdx]->returnBook();
      // A special book class that when passed to setBooksBorrowed removes a book from the list of books on loan
      Book terminatorBook(bookId, "", "", "");
      (*memberList)[foundMemberIdx]->setBooksBorrowed(terminatorBook);
      return;
    }
  }

  // If the Member has no book with the corresponding bookId on loan then the following is displayed
  std::cout << "The member does not have the book with id#: " << bookId << " out on loan" << std::endl;
}

/*
  Displays all the books a Member currently has out on loan
  @param memberId the id of the member to check the loaned books of
  @param memberList a reference to the list of all members in the system
*/
void Librarian::displayBorrowedBooks(int memberId, std::vector<Member*>* memberList){
  int memberIdx;
  std::cout << std::endl;

  // Finds the index inside the memberList at which the Member with the corresponding memberId exists
  for(int i = 0; i < memberList->size(); i++){
    if(std::to_string(memberId) == (*memberList)[i]->getMemberId()){
      memberIdx = i;
      break;
    }
  }

  // Displays some details of the member
  std::cout << "NAME: " << (*memberList)[memberIdx]->getName() << std::endl;
  std::cout << "ADDRESS: " << (*memberList)[memberIdx]->getAddress() << std::endl;
  std::cout << "EMAIL: " << (*memberList)[memberIdx]->getEmail() << std::endl;

  std::vector<Book> loanedBooks = (*memberList)[memberIdx]->getBooksBorrowed();
  if(loanedBooks.size() <= 0){
    std::cout << "This member has not borrowed any books as of yet.\n";
    return;
  }

  // Displays all books the user has on loan
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

/*
  Calculates the total fines the Member should be charged due to overdue books
  @param memberId the id number of the member that is being checked
  @param memberList list of all members stored on the system
*/
void Librarian::calcFine(int memberId, std::vector<Member*>* memberList){
  int foundIdx;
  std::cout << std::endl;

  // Finds the index for where the Member with the corresponding is memberId is found in memberList
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
  const int FINE_RATE = 1;
  std::time_t currentTime = std::time(0);
  if(loanedBooks.size() > 0){
    std::cout << "[Overdue Books]" << std::endl;
    // Determines how overdue if at all, a book is. Calculates fines accordingly
    for(int i = 0; i < loanedBooks.size(); i++){
        std::time_t dueTime = loanedBooks[i].getDueDate().timestamp;
        // Calculates the time difference between the current time and the due date
        double timeDiff = std::difftime(currentTime, dueTime) / DAY_IN_SECONDS;
        // The book is overdue if the difference in time is a positive number
        if(timeDiff > 0){
          // Displays book information as well as fine incurred for that specific book
          std::cout << "BOOK ID#: " << loanedBooks[i].getBookId() << std::endl;
          std::cout << "BOOK NAME: " << loanedBooks[i].getBookName() << std::endl;
          std::cout << "OVERDUE BY: " << (int)timeDiff << " days" << std::endl;
          int fines = FINE_RATE * (int)timeDiff;
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

/*
  Return the staffId propery of the Librarian
  @return staffId the id number of the librarian
*/
int Librarian::getStaffId(){
  return staffId;
}

/*
  Sets the staffId property to the value of the provided argument
  @param staffId the id number the Librarian's staffId should be set to
*/
void Librarian::setStaffId(int staffId){
  this->staffId = staffId;
}

/*
  Return the salary property of the Librarian
  @return salary the librarian's salary
*/
int Librarian::getSalary(){
  return salary;
}

/*
  Sets the salary property to the value of the provided argument
  @param salary the Librarian's new salary
*/
void Librarian::setSalary(int salary){
  this->salary = salary;
}
