#include "Course.h"

// Default constructor
Course::Course() : creditHours(0) {}

// Parameterized constructor
Course::Course(std::string id, std::string name, std::string desc, int credits) {
    courseId = id;
    courseName = name;
    description = desc;
    creditHours = credits;
}

// Getters
std::string Course::getCourseId() const { return courseId; }
std::string Course::getCourseName() const { return courseName; }
std::string Course::getDescription() const { return description; }
int Course::getCreditHours() const { return creditHours; }

// Setters
void Course::setCourseId(const std::string& id) { courseId = id; }
void Course::setCourseName(const std::string& name) { courseName = name; }
void Course::setDescription(const std::string& desc) { description = desc; }
void Course::setCreditHours(int credits) { creditHours = credits; }
