/*
person.cpp
author: M00829986
Created: 12/1/2024
Updated: 12/1/2024
*/
#include "person.h"

/*
  Return the name property of the Person
  @return name the name of the Person
*/
std::string Person::getName(){
  return name;
}

/*
  Set the name property of the Person to that of the provided argument
  @param name the new name of the Person
*/
void Person::setName(std::string name){
  this->name = name;
}

/*
  Return the email property of the Person
  @return email the email address of the Person
*/
std::string Person::getEmail(){
  return email;
}

/*
  Set the email property of the Person to that of the provided argument
  @param email the new email address of the Person
*/
void Person::setEmail(std::string email){
  this->email = email;
}

/*
  Return the address property of the Person
  @return the address of the Person
*/
std::string Person::getAddress(){
  return address;
}

/*
  Set the address property of the Person to that of the provided argument
  @param address the new address of the Person
*/
void Person::setAddress(std::string address){
  this->address = address;
}
