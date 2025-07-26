#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>

class Enrollment {
private:
    std::string enrollmentId;
    std::string studentId;
    std::string courseId;
    std::string enrollmentDate;
    std::string grade;

public:
    Enrollment(); // Default constructor
    Enrollment(std::string id, std::string sid, std::string cid);

    // Getters
    std::string getEnrollmentId() const;
    std::string getStudentId() const;
    std::string getCourseId() const;
    std::string getEnrollmentDate() const;
    std::string getGrade() const;

    // Setters
    void setEnrollmentId(const std::string& id);
    void setStudentId(const std::string& sid);
    void setCourseId(const std::string& cid);
    void setEnrollmentDate(const std::string& date);
    void setGrade(const std::string& g);
};

#endif // ENROLLMENT_H
