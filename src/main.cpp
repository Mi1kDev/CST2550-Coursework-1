/*
  main.cpp
  Author: M00829986
  Created: 28/12/2024
  Updated: 1/11/2024
*/
#include "classes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

// Reads data from a provided csv file and creates a list of books using the provided data
std::vector<Book*> loadBooks(std::string filepath){
  // Initialization of book vector
  std::vector<Book *> books;
  std::string content;
  // Input stream used to read from a file
  std::ifstream BookList;
  // Regex to check for data stored in between quotes
  std::regex quotePattern(R"("+[a-zA-Z0-9, ]+")");
  std::smatch m;
  // Opens the csv file
  BookList.open(filepath);
  if(BookList.is_open()){
    // Done to skip the first line of data which is usually headers of the file
    getline(BookList, content);
    int count = 1;
    try{
      // Loops through file until reaching EOF
      while(BookList){
        // Get line from the file
        getline(BookList, content);
        // If the first line is empty then it assumes the file is empty
        if(content.length() <= 0 && count == 1){
          // Throw an error
          throw 100;
        }
        // If the line has content in it then the following takes place
        if(content.length() > 0){
          // Checks whether there exists a section of string matching the quotation regex pattern
          std::regex_search(content, m, quotePattern);
          std::string edited;
          int j, tally;
          // If a match for the regex search is found then the following takes place
          if(m.size() > 0){
            // Loops through all matches in the line and replaces the line with a version with removed commas
            for(std::string x: m){
              edited = std::regex_replace(x, std::regex(","), "");
              content = std::regex_replace(content, std::regex(x), edited);
            }
          }
          std::stringstream ss(content);
          std::string temp;
          std::vector<std::string> bookProperties;
          int i = 0;
          // Splits the line using the , delimiter
          while(getline(ss, temp, ',')){
            // Each part of the split line is stored in a vector
            bookProperties.push_back(temp);
            // Error is thrown if the line element is empty
            if(bookProperties[i].length() <= 0){
              throw 100;
            }
            i++;
          }
          // Constructs a new book class and adds it to the books vector
          books.push_back(new Book(stoi(bookProperties[0]), bookProperties[1], bookProperties[3], bookProperties[4]));
          count++;
        }
      }
    }catch(...){
      // Error message displayed if the format of the datafile is incorrect
      std::cout << "Please check the format of the input datafile.";
      exit(0);
    }
    // Closes file
    BookList.close();
  }
  std::cout << "The following books were loaded." << std::endl;
  std::cout << std::endl << "ID: BOOKNAME" << std::endl;
  for(Book *b : books){
    std::cout << b->getBookId() << ": " << b->getBookName() << std::endl;
  }
  std::cout << "Enter any key to continue: ";
  std::cin.ignore();
  std::cout << "\033[2J\033[1;1H";
  return books;
}
// Allows the user to create a librarian class by providing necessary input
Librarian  createLibrarian(){
  int staffId, salary;
  std::string name, address, email, dump;
  bool validated = false;
  bool nameValid = false, addressValid = false, emailValid = false, idValid = false, salaryValid = false;
  std::cout << "[ Please enter the details of the current Librarian ]" << std::endl;
  // Will loop until all input is considered validated
  std::cin;
  while(!validated){
    // Allows the user to enter the librarian's name
    while(!nameValid){
      std::cout << "Name: ";
      std::getline(std::cin, name);
      if(name.length() > 0){
        nameValid = true;
      }else{
        std::cout << "Name must contain at least a single character\n\n";
      }
    }
    // Allows the user to enter the librarian's address
    while(!addressValid){
      std::cout << "Address: ";
      std::getline(std::cin, address);
      if(address.length() > 0){
        addressValid = true;
      }else{
        std::cout << "Address must contain at least a single character\n\n";
      }
    }
    // Allows the user to enter the librarian's email
    while(!emailValid){
      std::cout << "Email: ";
      std::getline(std::cin, email);
      std::regex emailPattern("[a-zA-Z0-9](.+)(@){1}[a-zA-Z0-9](.+)((.){1}[a-zA-Z](.+))(.+)");
      if(!regex_match(email, emailPattern)){
        std::cout << "Invalid format for email\n\n";
      }else{
        emailValid = true;
      }
    }
    std::string salaryStr, staffIdStr;
    // Regex pattern to determine whether provided input is an integer or not
    std::regex integerPattern("[0-9]+");
    // Allows the user to enter the librarian's id
    while(!idValid){
      std::cout << "ID #: ";
      std::cin >> staffIdStr;
      std::cin.ignore();
      // If the input is not an integer then an error message is displayed
      if(!regex_match(staffIdStr, integerPattern)){
        std::cout << "Input must be an integer\n\n";
      }else{
        staffId = std::stoi(staffIdStr);
        idValid = true;
      }
    }
    // Allows the user to enter the librarian's salary
    while(!salaryValid){
      std::cout << "Salary: ";
      std::cin >> salaryStr;
      std::cin.ignore();
      // If the input is not an integer then an error message is displayed
      if(!regex_match(salaryStr, integerPattern)){
        std::cout << "Input must be an integer \n\n";
      }else{
        salary = std::stoi(salaryStr);
        salaryValid = true;
      }
    }
    std::string opt;
    bool inputCorrect = false;
    // Asks the user whether the input is valid
    while(!inputCorrect){
      std::cout << "Are you sure this is information is correct? [YES] or [NO]: ";
      std::getline(std::cin, opt);
      // If the user says the input is valid then the loop can end otherwise they are reprompted to fix their errors
      if(opt == "YES"){
        validated = true;
        inputCorrect = true;
      }else if(opt == "NO"){
        std::cout << std::endl;
        inputCorrect = true;
        nameValid = false;
        addressValid = false;
        emailValid = false;
        idValid = false;
        salaryValid = false;
      }else{
        std::cout << "Invalid option selected. Either check that your input is spelt correctly or provide valid input\n\n";
      }
    }
  }
  // Creates a librarian class using the provided data
  Librarian l1(staffId, name, address, email, salary);
  return l1;
}
// Displays menu for user to interact with
int displayMenu(){
  std::cout << "1. Add Member" << std::endl;
  std::cout << "2. Issue Book" << std::endl;
  std::cout << "3. Return Book" << std::endl;
  std::cout << "4: Display Books Borrowed by a Member" << std::endl;
  std::cout << "5. Exit" << std::endl;

  std::string selection;
  std::regex integerPattern("[1-5]{1}");
  // Asks the user to select an option (function) to execute
  while(true){
    std::cout << "Please select an option: ";
    std::cin >> selection;
    std::cin.ignore();
    // If the selection is not an integer then an error is prompted and the user is asked for input once more
    if(!regex_match(selection, integerPattern)){
      std::cout << "Invalid selection made\n\n";
    }else{
      // returns the integer form of the provided selection
      return std::stoi(selection);
    }
  }
  return 0;
}
// Start of program
std::string initialize(){
  bool promptingStart = true;
  while(promptingStart){
    // Prompts the user to either start or exit the program
    std::cout << "[START] or [EXIT] program: ";
    std::string opt;
    std::cin >> opt;
    // If the user selects exit then the program is terminated
    if(opt == "EXIT"){
      std::cout << "Terminating program...";
      exit(0);
    // If the user selects start then the following occurs
    }else if(opt == "START"){
      std::string filepath;
      bool acceptingFilepath = true;
      // Asks the user to enter a file to load books from
      while(acceptingFilepath){
        std::cout << "Please enter the file path to load books from or [EXIT] to leave: ";
        std::cin >> filepath;
        std::cin.ignore();
        // If the user enters EXIT then the program terminates
        if(filepath == "EXIT"){
          std::cout << "Terminating program...";
          exit(0);
        }
        std::ifstream file(filepath);
        // If the file exists then the function returns the filepath
        if(file){
          file.close();
          return filepath;
        }else{
          // Otherwise an error message is outputted
          std::cout << "The provided file does not exist!\n\n";
        }
      }
      promptingStart = false;
    }else{
      // If the user enters neither START nor exit then an error message is outputted
      std::cout << "Invalid Option Provided!\n\n";
    }
  }
  return "";
}
// Adds a member to the member list
void addMember(Librarian* librarian, std::vector<Member*>* memberList){
  std::cout << std::endl;
  bool continueAdding = true, optionSelected;
  std::string memberContinue;
  // Loops until the user says they do not wish to add another member
  while(continueAdding){
    // Calls the addMember method of the librarian class
    librarian->addMember(memberList);
    optionSelected = false;
    // Asks the user to select either YES or NO
    while(!optionSelected){
      std::cout << "Would you like to add another member? [YES] or [NO]: ";
      std::cin >> memberContinue;
      std::cin.ignore();
      // If the user selects NO then the loop ends
      if(memberContinue == "NO"){
        continueAdding = false;
        optionSelected = true;
      // If the user selects YES then the loop continues
      }else if(memberContinue == "YES"){
        std::cout << std::endl;
        optionSelected = true;
      }else{
        // If an invalid selection is provided then an error message is displayed
        std::cout << "Invalid Option selected\n\n";
      }
    }
  }
}

void returnBook(Librarian* librarian, std::vector<Member *>* memberList, std::vector<Book*>* bookList){
  std::cout << std::endl;
  bool continueReturning = true;
  bool memberIdValid = false, bookIdValid = false, optionSelected;
  std::regex integerPattern("[0-9]+");
  std::string memberContinue, memberIdStr, bookIdStr;
  std::string option;
  int memberId, bookId;

  while(continueReturning){
    while(!memberIdValid){
      std::cout << "Please enter the id number of the member returning a book: ";
      std::cin >> memberIdStr;
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        memberId = stoi(memberIdStr);
        memberIdValid = true;
      }
    }
    while(!bookIdValid){
      std::cout << "Please enter the id number of the book being returned: ";
      std::cin >> bookIdStr;
      if(!std::regex_match(bookIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        bookId = stoi(bookIdStr);
        bookIdValid = true;
      }
    }
    librarian->calcFine(memberId, memberList);
    librarian->returnBook(memberId, bookId, memberList, bookList);
    optionSelected = false;
    while(!optionSelected){
      std::cout << "Would you like to return another book? [YES] or [NO]: ";
      std::cin >> option;
      if(option == "YES"){
        std::cout << std::endl;
        optionSelected = true;
        memberIdValid = false;
        bookIdValid = false;
      }else if(option == "NO"){
        continueReturning = false;
        optionSelected = true;
      }else{
        std::cout << "Invalid Option selected \n\n";
      }
    }
  }
}
// Issues a book to a member
void bookIssuing(Librarian *librarian, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  int memberId, bookId;
  std::string memberIdStr, bookIdStr;
  std::regex integerPattern("[0-9]+");
  bool valid = false;
  bool bookIdValid = false, memberIdValid = false;
  std::cout << std::endl;
  // Loops until all inputs are validated
  while(!valid){
    // Asks the user to enter the member id of the member the book is being issued to
    while(!bookIdValid){
      std::cout << "Please enter the member id the book is being issued to: ";
      std::cin >> memberIdStr;
      // If the input is not an integer then an error message is displayed and the user is reprompted for input
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        // Converts the input into an integer value
        memberId = stoi(memberIdStr);
        bookIdValid = true;
      }
    }
    // Asks the user to enter the if og the book that is to be issued
    while(!memberIdValid){
      std::cout << "Please enter the book id of the book being issued: ";
      std::cin >> bookIdStr;
      // If the input is an integer then an error message is displayed and the user is reprompted for input
      if(!std::regex_match(bookIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        // Converts the input into an integer value
        bookId = stoi(bookIdStr);
        memberIdValid = true;
      }
    }
    // Executes the issueBook method of the librarian class
    librarian->issueBook(memberId, bookId, memberList, bookList);
    // Asks the user whether they would like to issue another book
    bool optionSelected = false;
    while(!optionSelected){
      std::string opt;
      std::cout << "Would you like to issue another book? [YES] or [NO]: ";
      std::cin >> opt;
      // If the user enters yes then the loop continues and the uset is asked to enter data once more
      if(opt == "YES"){
        std::cout << std::endl;
        optionSelected = true;
        memberIdValid = false;
        bookIdValid = false;
      // If the user enters no then the loop ends
      }else if(opt == "NO"){
        valid = true;
        optionSelected = true;
      }else{
        // Error message displayed if invalid input given
        std::cout << "Invalid Option selected\n\n";
      }
    }
  }
}
// Displays all books borrowed by a certain member
void displayMembersBooks(Librarian* librarian, std::vector<Member*>* memberList){
  std::string memberIdStr;
  int memberId;
  bool memberIdValid = false;
  std::regex integerPattern("[0-9]+");
  bool valid = false;
  std::string opt;
  // Loops until data is valid
  while(!valid){
    // Asks the user to enter the id of the member to display the loaned books of the member
    while(!memberIdValid){
      std::cout << "Please enter the ID # of the member: ";
      std::cin >> memberIdStr;
      // If the input is not an integer then an error message is displayed and user is reprompted for input
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID # must be an integer\n\n";
      }else{
        memberId = stoi(memberIdStr);
        memberIdValid = true;
      }
    }
    // Calls the displayBorrowedBooks method of the librarian class
    librarian->displayBorrowedBooks(memberId, memberList);
    bool optionSelected = false;
    // Asks the user whether they would like to view the loaned books of another member
    while(!optionSelected){
      std::cout << "Would you like to search another ID #? [YES] or [NO]: ";
      std::cin >> opt;
      // If the user selects yes then the loop continues and the user is asked to enter a member id once more
      if(opt == "YES"){
        std::cout << std::endl;
        optionSelected = true;
        memberIdValid = false;
      }else if(opt == "NO"){
        valid = true;
        optionSelected = true;
      }else{
        // Any other input will yield an error message
        std::cout << "Invalid Option was selected\n\n";
      }
    }
  }
}
int main(){
  // Gets the file path of the csv provided in the initialize() function
  std::string bookFilePath = initialize();
  // Gets a book list loaded from the csv file
  std::vector<Book *> bookList = loadBooks(bookFilePath);
  // Initializes a vector to store the members on the system
  std::vector<Member *> memberList;
  // Creates a librarian class via the createLibrarian function
  Librarian librarian = createLibrarian();
  bool active = true;
  int opt;
  // Loop continues until the user selects the option corresponding with the exit function
  while(active){
    std::cout << std::endl;
      // Displays menu options and gets the input the user provides
      opt = displayMenu();
      // executes the function corresponding to the selected input
      if(opt == 1){
        addMember(&librarian, &memberList);
      }else if(opt == 2){
        bookIssuing(&librarian, &memberList, &bookList);
      }else if(opt == 3){
        returnBook(&librarian, &memberList, &bookList);
      }else if(opt == 4){
        displayMembersBooks(&librarian, &memberList);
      }else if(opt == 5){
        std::cout << "Exiting..." << std::endl;
        active = false;
      }
  }

}
