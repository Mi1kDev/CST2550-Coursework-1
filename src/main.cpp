/*
  main.cpp
  Author: M00829986
  Created: 28/12/2024
  Updated: 12/1/2024
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include "librarian.h"
#include "book.h"
#include "member.h"

void clearScreen();
bool findIdMember(std::vector<Member*>, int);
bool findBookId(std::vector<Book*>, int);
bool inputReprompt();
void displayMembersBooks(Librarian*, std::vector<Member*>*);
void returnBook(Librarian*, std::vector<Member*>*, std::vector<Book*>*);
void bookIssuing(Librarian*, std::vector<Member*>*, std::vector<Book*>*);
void addMember(Librarian*, std::vector<Member*>*);
int displayMenu();
Librarian createLibrarian();
std::vector<Book*> loadBooks(std::string);
std::string initialize();
int main();

/*
  Clears the console
*/
void clearScreen(){
  std::cout << "\033[2J\033[1;1H";
}


/*
  Helper function used to determine if a member with a provided id exists in the system
  @param memberList list of all members in the system
  @param id member id to search for
  @return [true|false] depending on whether a match for the id was found or not
*/
bool findIdMember(std::vector<Member*>* memberList, int id){
  // Attempts to find the id inside the list of members, returns a true value if it does, otherwise returns false
  for(int i = 0; i < memberList->size(); i++){
    if(id == stoi((*memberList)[i]->getMemberId())){
      return true;
    }
  }
  return false;
}

/*
  Helper function used to determine if a book with a provided id exists in the system
  @param bookList list of all books loaded in the system
  @param id book id to search for
  @return [true|false] depending on whether id was found or not
*/
bool findBookId(std::vector<Book*>* bookList, int id){
    // Attempts to find the id inside the list of books, returns a true value if it does, otherwise returns false
  for(int i = 0; i < bookList->size(); i++){
    if(id == stoi((*bookList)[i]->getBookId())){
      return true;
    }
  }
  return false;
}

/*
  Helper function asking user if they would like to re-enter an id if one was previously not found
  @return confirmation boolean reflecting the choice made by the user
*/
bool inputReprompt(){
  std::string select;
  bool confirmation = false;
  std::cout << std::endl;
  // Asks user whether they would like to be prompted for re-entry
  while(!confirmation){
    std:: cout << "The provided id number was not found." << std::endl;
    std::cout << "Would you like to enter another id? [YES] or [NO]: ";
    std::cin >> select;
    if(select == "YES"){
      confirmation = true;
      std::cout << std::endl;
      return confirmation;
    }else if(select == "NO"){
      return confirmation;
    }else{
      std::cout << "Invalid Option selected \n\n";
    }
  }
  return confirmation;
}

/*
  Displays all books borrowed by a member
  @param librarian reference to Librarian instance utilized throughout system
  @param memberList list of all members stored in the system
*/
void displayMembersBooks(Librarian* librarian, std::vector<Member*>* memberList){
  std::string memberIdStr;
  int memberId;
  bool memberIdValid = false;
  std::regex integerPattern("[0-9]+");
  bool valid = false;
  std::string opt;

  std::cout << std::endl;

  // If there are no members then the function terminates
  if(memberList->size() <= 0){
    std::cout << "There are no members in the system currently\n\n";
    return;
  }

  // Allows for repeated execution until stopped by the user
  while(!valid){
    // Asks the user to enter the id of the member to display the loaned books of the member. Ensures input is an integer and id exists in memberList
    while(!memberIdValid){
      std::cout << "Please enter the ID # of the member: ";
      std::cin >> memberIdStr;
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID # must be an integer\n\n";
      }else{
        memberId = stoi(memberIdStr);
        if(findIdMember(memberList, memberId)){
          memberIdValid = true;
        }else{
          if(!inputReprompt()){
            return;
          }
        }

      }
    }
    // Calls the displayBorrowedBooks method of the librarian class
    librarian->displayBorrowedBooks(memberId, memberList);
    std::cout << std::endl;
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

/*
  Wrapper function for Librarian class's returnBook method. Ensures data is valid before being used
  @param librarian reference to Librarian instance used throughout system
  @param memberList list of all members in the system
  @param bookList list of all books loaded in the system
*/
void returnBook(Librarian* librarian, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  std::cout << std::endl;
  bool continueReturning = true;
  bool memberIdValid = false, bookIdValid = false, optionSelected;
  std::regex integerPattern("[0-9]+");
  std::string memberContinue, memberIdStr, bookIdStr;
  std::string option;
  std::string select;
  int memberId, bookId;

  // Stops the function if either there are no members or there are no books
  if(memberList->size() <= 0){
    std::cout << "There are currently no members in the system, therefore books cannot be returned\n\n";
    return;
  }
  if(bookList->size() <= 0){
    std::cout << "No books available.\n\n";
    return;
  }

  // Allows for repeated book returns until stopped by the user
  while(continueReturning){
    // Ensures the memberId entered is of valid format and exists in the list of members
    while(!memberIdValid){
      std::cout << "Please enter the id number of the member returning a book: ";
      std::cin >> memberIdStr;
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";

      }else{
        memberId = stoi(memberIdStr);
        if(findIdMember(memberList, memberId)){
          memberIdValid = true;
        }else{
          if(!inputReprompt()){
            return;
          }
        }
      }
    }
    // Ensures the bookId entered is of valid format and exists in the list of books
    while(!bookIdValid){
      std::cout << "Please enter the id number of the book being returned: ";
      std::cin >> bookIdStr;
      if(!std::regex_match(bookIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        bookId = stoi(bookIdStr);
        if(findBookId(bookList, bookId)){
          bookIdValid = true;
        }else{
          if(!inputReprompt()){
            return;
          }
        }
      }
    }

    librarian->returnBook(memberId, bookId, memberList, bookList);
    std::cout << std::endl;
    optionSelected = false;
    // Provides the user with the option to continue returning books
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

/*
  Wrapper function for Librarian class's issueBook method. Ensures data is validated
  @param librarian reference to Librarian instance used throughout system
  @param memberList list of all members stored in the system
  @param bookList list of all books loaded in the system
*/
void bookIssuing(Librarian *librarian, std::vector<Member*>* memberList, std::vector<Book*>* bookList){
  int memberId, bookId;
  std::string memberIdStr, bookIdStr;
  std::regex integerPattern("[0-9]+");
  bool valid = false;
  bool bookIdValid = false, memberIdValid = false;
  std::cout << std::endl;

  // If there are no members or no books then the function ends
  if(memberList->size() <= 0){
    std::cout << "There are currently no members in the system, therefore books cannot be issued\n\n";
    return;
  }
  if(bookList->size() <= 0){
    std::cout << "No books available to be issued.\n\n";
    return;
  }

  // Allows user to issue books repeatedly until stopped by user
  while(!valid){
    // Asks the user to enter the member id of the member the book is being issued to. Ensures the input is of valid format and that the memberId exists in the memberList
    while(!memberIdValid){
      std::cout << "Please enter the member id the book is being issued to: ";
      std::cin >> memberIdStr;
      if(!std::regex_match(memberIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        memberId = stoi(memberIdStr);
        if(findIdMember(memberList, memberId)){
          memberIdValid = true;
        }else{
          if(!inputReprompt()){
            return;
          }
        }
      }
    }
    // Asks the user to enter the id of the book being issued. Ensures the input is of valid format and that the bookId exists in the bookList
    while(!bookIdValid){
      std::cout << "Please enter the book id of the book being issued: ";
      std::cin >> bookIdStr;
      if(!std::regex_match(bookIdStr, integerPattern)){
        std::cout << "ID must be an integer\n\n";
      }else{
        bookId = stoi(bookIdStr);
        if(findBookId(bookList, bookId)){
          bookIdValid = true;
        }else{
          if(!inputReprompt()){
            return;
          }
        }
      }
    }
    std::cout << std::endl;
    // Executes the issueBook method of the librarian class
    librarian->issueBook(memberId, bookId, memberList, bookList);
    std::cout << std::endl;
    bool optionSelected = false;

    // Asks the user whether they would like to issue another book
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

/*
  Wrapper function for the Librarian method addMember. Allows for quick, repeated execution of the function
  @param librarian reference to the librarian class instance throughout the program
  @param memberlist list of all members in the system
*/
void addMember(Librarian* librarian, std::vector<Member*>* memberList){
  std::cout << std::endl;
  bool continueAdding = true, optionSelected;
  std::string memberContinue;
  // Allows the user to continue adding members until they select NO
  while(continueAdding){
    librarian->addMember(memberList);
    optionSelected = false;
    // Asks the user to select either YES or NO, reprompts if given invalid input
    while(!optionSelected){
      std::cout << "Would you like to add another member? [YES] or [NO]: ";
      std::cin >> memberContinue;
      std::cin.ignore();
      // If the user selects NO then the loop ends
      if(memberContinue == "NO"){
        continueAdding = false;
        optionSelected = true;
      // If the user selects YES then the loop continues and the user can create another member
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

/*
  Displays the menu providing the user all the options and operations they can perform
  @return selection (as int) the option selected by the user
*/
int displayMenu(){
  std::cout << "[Library Management Menu]" << std::endl;
  std::cout << "1. Add Member" << std::endl;
  std::cout << "2. Issue Book" << std::endl;
  std::cout << "3. Return Book" << std::endl;
  std::cout << "4: Display Books Borrowed by a Member" << std::endl;
  std::cout << "5: Clear Screen" << std::endl;
  std::cout << "6. Exit" << std::endl;
  std::cout << std::endl;

  std::string selection;
  std::regex integerPattern("[1-6]{1}");
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

/*
  Creates a Librarian class using details provided by the user
  @return l1 instance of Librarian class
*/
Librarian  createLibrarian(){
  int staffId, salary;
  std::string name, address, email, dump;
  std::regex namePattern("[a-zA-Z -]+");
  std::regex addressPattern("[a-zA-Z0-9 -]+");
  std::regex emailPattern("[a-zA-Z0-9](.+)(@){1}[a-zA-Z0-9](.+)((.){1}[a-zA-Z](.+))(.+)");
  bool validated = false;
  bool nameValid = false, addressValid = false, emailValid = false, idValid = false, salaryValid = false;
  std::cout << "[ Please enter the details of the current Librarian ]" << std::endl;
  std::cin;

  // Loop used to allow user to confirm that their inputted information is correct
  while(!validated){
    // Checks that entered name is of valid format
    while(!nameValid){
      std::cout << "Name: ";
      std::getline(std::cin, name);
      if(std::regex_match(name, namePattern)){
        nameValid = true;
      }else{
        std::cout << "Name must consist of only alphabet characters and hyphens\n\n";
      }
    }
    // Checks that entered address is of valid format
    while(!addressValid){
      std::cout << "Address: ";
      std::getline(std::cin, address);
      if(std::regex_match(address, addressPattern)){
        addressValid = true;
      }else{
        std::cout << "Address must contain at least a single alphanumeric character\n\n";
      }
    }
    // Checks that entered email is of valid format
    while(!emailValid){
      std::cout << "Email: ";
      std::getline(std::cin, email);
      if(!regex_match(email, emailPattern)){
        std::cout << "Invalid format for email\n\n";
      }else{
        emailValid = true;
      }
    }
    std::string salaryStr, staffIdStr;
    // Regex pattern to determine whether provided input is an integer or not
    std::regex integerPattern("[0-9]+");

    // Checks that entered id is an integer
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

    // Checks that entered salary is an integer
    while(!salaryValid){
      std::cout << "Salary: ";
      std::cin >> salaryStr;
      std::cin.ignore();
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

/*
  Loads books from a provided file into a vector of Book classes
  @param filepath path to source file which contains data of all books
  @return books a list of all the books read from the source file
*/
std::vector<Book*> loadBooks(std::string filepath){
  std::vector<Book *> books;
  std::string content;
  std::ifstream BookList;
  // Pattern to check whether a section of string is within quotation marks
  std::regex quotePattern(R"("+[a-zA-Z0-9, ]+")");
  std::smatch m;
  BookList.open(filepath);
  if(BookList.is_open()){
    // Skips first line of file. In CSVs this is usually titles and headings
    getline(BookList, content);
    int count = 1;
    try{
      while(BookList){
        getline(BookList, content);
        if(content.length() <= 0 && count == 1){
          throw 100;
        }
        if(content.length() > 0){
          // Checks if there exists any section of the string matching the quotation pattern
          std::regex_search(content, m, quotePattern);
          std::string edited;
          int j, tally;
          if(m.size() > 0){
            // Replaces all commas in those quotation mark sections with an empty string and then replaces the quotation mark section with the edited string
            for(std::string x: m){
              edited = std::regex_replace(x, std::regex(","), "");
              content = std::regex_replace(content, std::regex(x), edited);
            }
          }
          std::stringstream ss(content);
          std::string temp;
          std::vector<std::string> bookProperties;
          int i = 0;
          // Splits line by , and stores each property into a vector for Book creation
          while(getline(ss, temp, ',')){
            bookProperties.push_back(temp);
            if(bookProperties[i].length() <= 0){
              throw 100;
            }
            i++;
          }
          books.push_back(new Book(stoi(bookProperties[0]), bookProperties[1], bookProperties[3], bookProperties[4]));
          count++;
        }
      }
    }catch(...){
      std::cout << "Please check the format of the input datafile.";
      exit(0);
    }
    BookList.close();
  }

  // Displays all books read from the file
  std::cout << "The following books were loaded." << std::endl;
  std::cout << std::endl << "ID: BOOKNAME" << std::endl;
  for(Book* b : books){
    std::cout << b->getBookId() << ": " << b->getBookName() << std::endl;
  }
  std::cout << "Enter any key to continue: ";
  std::cin.ignore();
  clearScreen();
  return books;
}

/*
  Program start. Provides options to exit the program. Accepts path to file where books will be loaded from
  @return filepath Path to file where books will be loaded from
*/
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

/*
  Main function
  @return int status code
*/
int main(){
  // Gets the file path of the csv provided in the initialize() function
  std::string bookFilePath = initialize();
  // Gets a book list loaded from the csv file
  std::vector<Book *> bookList = loadBooks(bookFilePath);
  // Initializes a vector to store the members on the system
  std::vector<Member *> memberList;
  // Creates a librarian class via the createLibrarian function
  Librarian librarian = createLibrarian();
  std::cout << std::endl;
  bool active = true;
  int opt;
  // Loop continues until the user selects the option corresponding with the exit function
  while(active){
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
          clearScreen();
      }else if(opt == 6){
        std::cout << "Exiting..." << std::endl;
        active = false;
      }
  }
  return 0;
}
