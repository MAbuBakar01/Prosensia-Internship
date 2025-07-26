#include "Enrollment.h"
#include "Utility.h" // For getCurrentDate

// Default constructor
Enrollment::Enrollment() {}

// Parameterized constructor
Enrollment::Enrollment(std::string id, std::string sid, std::string cid) {
    enrollmentId = id;
    studentId = sid;
    courseId = cid;
    grade = "Not Graded";
    enrollmentDate = getCurrentDate(); // Uses utility function
}

// Getters
std::string Enrollment::getEnrollmentId() const { return enrollmentId; }
std::string Enrollment::getStudentId() const { return studentId; }
std::string Enrollment::getCourseId() const { return courseId; }
std::string Enrollment::getEnrollmentDate() const { return enrollmentDate; }
std::string Enrollment::getGrade() const { return grade; }

// Setters
void Enrollment::setEnrollmentId(const std::string& id) { enrollmentId = id; }
void Enrollment::setStudentId(const std::string& sid) { studentId = sid; }
void Enrollment::setCourseId(const std::string& cid) { courseId = cid; }
void Enrollment::setEnrollmentDate(const std::string& date) { enrollmentDate = date; }
void Enrollment::setGrade(const std::string& g) { grade = g; }
