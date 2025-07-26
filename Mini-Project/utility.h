#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <ctime>
#include <cctype>

// Gets the current date in YYYY-MM-DD format
std::string getCurrentDate();

// Input Validation Functions
bool isValidName(const std::string& name);
bool isValidPhoneNumber(const std::string& phone);
bool isValidEmail(const std::string& email);

#endif // UTILITY_H
