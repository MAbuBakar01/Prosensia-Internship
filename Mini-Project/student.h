#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string studentId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phoneNumber;
    std::string registrationDate;
public:
    Student(); // Default constructor
    Student(std::string id, std::string fname, std::string lname, std::string em, std::string phone);

    // Getters
    std::string getStudentId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getPhoneNumber() const;
    std::string getRegistrationDate() const;

    // Setters
    void setStudentId(const std::string& id);
    void setFirstName(const std::string& fname);
    void setLastName(const std::string& lname);
    void setEmail(const std::string& em);
    void setPhoneNumber(const std::string& phone);
    void setRegistrationDate(const std::string& date);
};

#endif // STUDENT_H
