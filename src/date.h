/*
date.h
Author: M00829986
Created: 28/12/2024
Updated: 12/1/2024
*/
#ifndef _DATE_H
#define _DATE_H
#include <ctime>

// Struct which provides a simple interface to store date information
struct Date{
  int day;
  int month;
  int year;
  time_t timestamp;
};
#endif
