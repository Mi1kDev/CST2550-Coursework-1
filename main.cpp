#include "classes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<Book *> loadBooks(std::string filepath){
  std::vector<Book *> books;
  std::string content;
  std::ifstream BookList;
  BookList.open(filepath);
  if(BookList.is_open()){
    getline(BookList, content);
    while(BookList){
      getline(BookList, content);
      std::stringstream ss(content);
      std::string temp;
      std::string bookProperties[7];
      int i = 0;
      while(getline(ss, temp, ',')){
        bookProperties[i] = temp;
        i++;
      }
      try{
        books.push_back(new Book(std::stoi("2"), bookProperties[1], bookProperties[3], bookProperties[4]));
      }catch(std::string id){
        std::cout << "Cause of Error " << id;
      }
    }
  }
  return books;
}
int main(){
  const std::string libraryBooks = "library_books.csv";
  std::vector<Book *> loadedBooks = loadBooks(libraryBooks);
  for(Book * b: loadedBooks){
    std::cout << b->getBookName();
  }
}
