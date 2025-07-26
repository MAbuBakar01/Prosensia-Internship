#include "Student.h"
#include "Utility.h" // For getCurrentDate

// Default constructor
Student::Student() {}

// Parameterized constructor
Student::Student(std::string id, std::string fname, std::string lname, std::string em, std::string phone) {
    studentId = id;
    firstName = fname;
    lastName = lname;
    email = em;
    phoneNumber = phone;
    registrationDate = getCurrentDate(); // Uses utility function
}

// Getters
std::string Student::getStudentId() const { return studentId; }
std::string Student::getFirstName() const { return firstName; }
std::string Student::getLastName() const { return lastName; }
std::string Student::getFullName() const { return firstName + " " + lastName; }
std::string Student::getEmail() const { return email; }
std::string Student::getPhoneNumber() const { return phoneNumber; }
std::string Student::getRegistrationDate() const { return registrationDate; }

// Setters
void Student::setStudentId(const std::string& id) { studentId = id; }
void Student::setFirstName(const std::string& fname) { firstName = fname; }
void Student::setLastName(const std::string& lname) { lastName = lname; }
void Student::setEmail(const std::string& em) { email = em; }
void Student::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
void Student::setRegistrationDate(const std::string& date) { registrationDate = date; }
