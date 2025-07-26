#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseId;
    std::string courseName;
    std::string description;
    int creditHours;
public:
    Course(); // Default constructor
    Course(std::string id, std::string name, std::string desc, int credits);

    // Getters
    std::string getCourseId() const;
    std::string getCourseName() const;
    std::string getDescription() const;
    int getCreditHours() const;

    // Setters
    void setCourseId(const std::string& id);
    void setCourseName(const std::string& name);
    void setDescription(const std::string& desc);
    void setCreditHours(int credits);
};

#endif // COURSE_H
