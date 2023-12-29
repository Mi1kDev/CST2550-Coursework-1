#include "classes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

std::vector<Book *> loadBooks(std::string filepath){
  std::vector<Book *> books;
  std::string content;
  std::ifstream BookList;
  BookList.open(filepath);
  if(BookList.is_open()){
    getline(BookList, content);
    int count = 1;
    try{
      while(BookList){
        getline(BookList, content);
        std::stringstream ss(content);
        if(content.length() <= 0 && count == 1){
          throw 100;
        }
        if(content.length() > 0){
          std::string temp;
          std::string bookProperties[7];
          int i = 0;
          while(getline(ss, temp, ',')){
            bookProperties[i] = temp;
            if(bookProperties[i].length() <= 0){
              throw 100;
            }
            i++;
          }
          books.push_back(new Book(count, bookProperties[1], bookProperties[3], bookProperties[4]));
          count++;
        }
      }
    }catch(...){
      std::cout << "Please check the format of the input datafile.";
      exit(0);
    }
    BookList.close();
  }
  std::cout << "Books have been loaded successfully" << std::endl;
  return books;
}
Librarian  createLibrarian(){
  int staffId, salary;
  std::string name, address, email;
  bool validated = false;
  std::cout << "[ Please enter the details of the current Librarian ]" << std::endl;
  while(!validated){
    while(true){
      std::cout << "Name: ";
      std::getline(std::cin, name);
      if(name.length() > 0){
        break;
      }else{
        std::cout << "Name must contain at least a single character\n\n";
      }
    }
    while(true){
      std::cout << "Address: ";
      std::getline(std::cin, address);
      if(address.length() > 0){
        break;
      }else{
        std::cout << "Address must contain at least a single character\n\n";
      }
    }
    while(true){
      std::cout << "Email: ";
      std::getline(std::cin, email);
      std::regex emailPattern("[a-zA-Z0-9](.+)(@){1}[a-zA-Z0-9](.+)((.){1}[a-zA-Z](.+))(.+)");
      if(!regex_match(email, emailPattern)){
        std::cout << "Invalid format for email\n\n";
      }else{
        break;
      }
    }
    std::string salaryStr, staffIdStr;
    std::regex integerPattern("[0-9]+");
    while(true){
      std::cout << "ID #: ";
      std::cin >> staffIdStr;
      std::cin.ignore();
      if(!regex_match(staffIdStr, integerPattern)){
        std::cout << "Input must be an integer\n\n";
      }else{
        staffId = std::stoi(staffIdStr);
        break;
      }
    }
    while(true){
      std::cout << "Salary: ";
      std::cin >> salaryStr;
      std::cin.ignore();
      if(!regex_match(salaryStr, integerPattern)){
        std::cout << "Input must be an integer \n\n";
      }else{
        salary = std::stoi(salaryStr);
        break;
      }
    }
    std::string opt;
    while(true){
      std::cout << "Are you sure this is information is correct? [YES] or [NO]: ";
      std::getline(std::cin, opt);
      if(opt == "YES"){
        validated = true;
        break;
      }else if(opt == "NO"){
        std::cout << std::endl;
        break;
      }else{
        std::cout << "Invalid option selected. Either check that your input is spelt correctly or provide valid input";
      }
    }
  }
  Librarian l1(staffId, name, address, email, salary);
  return l1;
}
int displayMenu(){
  std::cout << "1. Add Member" << std::endl;
  std::cout << "2. Issue Book" << std::endl;
  std::cout << "3. Return Book" << std::endl;
  std::cout << "4: Display Books Borrowed by a Member" << std::endl;
  std::cout << "5. Calculate Fines" << std::endl;
  std::cout << "6. Exit" << std::endl;

  std::string selection;
  std::regex integerPattern("[1-6]{1}");

  while(true){
    std::cout << "Please select an option: ";
    std::cin >> selection;
    std::cin.ignore();
    if(!regex_match(selection, integerPattern)){
      std::cout << "Invalid selection made\n\n";
    }else{
      return std::stoi(selection);
    }
  }
  return 0;
}
std::string initialize(){
  while(true){
    std::cout << "[START] or [EXIT] program: ";
    std::string opt;
    std::cin >> opt;
    if(opt == "EXIT"){
      std::cout << "Terminating program...";
      exit(0);
    }else if(opt == "START"){
      std::string filepath;
      while(true){
        std::cout << "Please enter the file path to load books from: ";
        std::cin >> filepath;
        std::cin.ignore();
        std::ifstream file(filepath);
        if(file){
          file.close();
          return filepath;
        }else{
          std::cout << "The provided file does not exist!\n\n";
        }
      }
      break;
    }else{
      std::cout << "Invalid Option Provided!\n\n";
    }
  }
  return "";
}
void addMember(Librarian *librarian, std::vector<Member *> *memberList){
  std::cout << std::endl;
  bool continueAdding = true;
  std::string memberContinue;
  while(continueAdding){
    librarian->addMember(memberList);
    while(true){
      std::cout << "Would you like to add another member? [YES] or [NO]: ";
      std::cin >> memberContinue;
      std::cin.ignore();
      if(memberContinue == "NO"){
        continueAdding = false;
        break;
      }else if(memberContinue == "YES"){
        std::cout << std::endl;
        break;
      }else{
        std::cout << "Invalid Option selected\n\n";
      }
    }
  }
}
void bookIssuing(Librarian *librarian, std::vector<Member *> *memberList, std::vector<Book *> *bookList){
  int memberId, bookId;
  std::string memberIdStr, bookIdStr;
  std::regex integerPattern("[0-9]+");
  bool valid = false;
  std::cout << std::endl;
  while(!valid){
    while(true){
      std::cout << "Please enter the member id the book is being issued to: ";
      std::cin >> memberIdStr;
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        memberId = stoi(memberIdStr);
        break;
      }
    }
    while(true){
      std::cout << "Please enter the book id of the book being issued: ";
      std::cin >> bookIdStr;
      if(!std::regex_match(bookIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        bookId = stoi(bookIdStr);
        break;
      }
    }
    librarian->issueBook(memberId, bookId, memberList, bookList);
    while(true){
      std::string opt;
      std::cout << "Would you like to issue another book? [YES] or [NO]: ";
      std::cin >> opt;
      if(opt == "YES"){
        std::cout << std::endl;
        break;
      }else if(opt == "NO"){
        valid = true;
        break;
      }else{
        std::cout << "Invalid Option selected\n\n";
      }
    }
  }
}
void displayMembersBooks(Librarian * librarian, std::vector<Member *> *memberList){
  std::string memberIdStr;
  int memberId;
  std::regex integerPattern("[0-9]+");
  bool valid = false;
  std::string opt;
  while(!valid){
    while(true){
      std::cout << "Please enter the ID # of the member: ";
      std::cin >> memberIdStr;

      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID # must be an integer";
      }else{
        memberId = stoi(memberIdStr);
        break;
      }
    }
    librarian->displayBorrowedBooks(memberId, memberList);
    while(true){
      std::cout << "Would you like to search another ID #? [YES] or [NO]: ";
      std::cin >> opt;
      if(opt == "YES"){
        std::cout << std::endl;
        break;
      }else if(opt == "NO"){
        valid = true;
        break;
      }else{
        std::cout << "Invalid Option was selected";
      }
    }
  }
}
int main(){
  std::string bookFilePath = initialize();
  std::vector<Book *> bookList = loadBooks(bookFilePath);
  std::vector<Member *> memberList;
  Librarian librarian = createLibrarian();
  bool active = true;
  int opt;
  while(active){
    std::cout << std::endl;
      opt = displayMenu();
      if(opt == 1){
        addMember(&librarian, &memberList);
      }else if(opt == 2){
        bookIssuing(&librarian, &memberList, &bookList);
      }else if(opt == 4){
        displayMembersBooks(&librarian, &memberList);
      }else if(opt == 6){
        std::cout << "Exiting..." << std::endl;
        active = false;
      }
  }

}
