#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "classes.h"


TEST_CASE("Class Construction", "[class_created]")
{
  Person p1;
  p1.setName("Bob");
  p1.setAddress("123 Alegra Way");
  p1.setEmail("ja@yahoo.co.uk");
  REQUIRE(p1.getName() == "Bob");
  REQUIRE(p1.getAddress() == "123 Alegra Way");
  REQUIRE(p1.getEmail() == "ja@yahoo.co.uk");

  Librarian l1(0, "Johnny", "123 Court Way", "johnny@yahoo.com", 200);
  REQUIRE(l1.getName() == "Johnny");
  REQUIRE(l1.getAddress() == "123 Court Way");
  REQUIRE(l1.getEmail() == "johnny@yahoo.com");
  REQUIRE(l1.getStaffId() == 0);
  REQUIRE(l1.getSalary() == 200);

  Book b1(0, "Goldilocks", "John", "Arbuckle");
  Date dueDate;
  dueDate.year = 2000;
  dueDate.month = 5;
  dueDate.day = 12;
  dueDate.timestamp = std::time(0);
  b1.setDueDate(dueDate);
  REQUIRE(b1.getBookId() == "0");
  REQUIRE(b1.getBookName() == "Goldilocks");
  REQUIRE(b1.getAuthorFirstName() == "John");
  REQUIRE(b1.getAuthorLastName() == "Arbuckle");
  REQUIRE(b1.getDueDate().year == dueDate.year);

  Member m1(0, "John", "123 Mayday Way", "john@may.com");
  m1.setBooksBorrowed(b1);
  REQUIRE(m1.getMemberId() == "0");
  REQUIRE(m1.getAddress() == "123 Mayday Way");
  REQUIRE(m1.getEmail() == "john@may.com");
  REQUIRE(m1.getBooksBorrowed()[0].getBookId() == b1.getBookId());

}
