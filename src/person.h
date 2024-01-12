#ifndef PERSON_H
#define PERSON_H
/*
person.h
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include <iostream>

// Implementation of Person class, its properties and methods
class Person{
  private:
    std::string name;
    std::string email;
    std::string address;
  public:
    std::string getName();
    void setName(std::string name);
    std::string getAddress();
    void setAddress(std::string address);
    std::string getEmail();
    void setEmail(std::string email);
};
#endif
