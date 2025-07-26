#ifndef PORTAL_H
#define PORTAL_H

#include <vector>
#include <string>
#include <fstream> 

#include "Student.h"
#include "Course.h"
#include "Enrollment.h"
#include "ContentHierarchy.h"
class Portal {
private:
    std::vector<Student> students;
    std::vector<Course> courses;
    std::vector<Enrollment> enrollments;
    std::vector<Topic> topics_data;
    std::vector<SubTopic> subtopics_data;
    std::vector<Lesson> lessons_data;

    // File paths for data storage
    const std::string STUDENTS_FILE = "students.csv";
    const std::string COURSES_FILE = "courses.csv";
    const std::string ENROLLMENTS_FILE = "enrollments.csv";
    const std::string TOPICS_FILE = "topics.csv";
    const std::string SUBTOPICS_FILE = "subtopics.csv";
    const std::string LESSONS_FILE = "lessons.csv";

    // Generate a unique ID based on the current size of vector
    std::string generateUniqueId(const std::string& prefix, int currentSize);

    // Helper for cascading deletes
    void deleteTopicCascading(const std::string& topicId);
    void deleteSubTopicCascading(const std::string& subTopicId);


public:
    Portal();
    // ~Portal(); // Destructor might not be needed if saveData is called explicitly

    // Student management functions
    void addStudent(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& phoneNumber);
    bool updateStudent(const std::string& studentId, const std::string& firstName, const std::string& lastName,
                      const std::string& email, const std::string& phoneNumber);
    bool deleteStudent(const std::string& studentId);
    Student* findStudent(const std::string& studentId); // Returns pointer, be careful with lifetime
    std::vector<Student> getAllStudents() const;

    // Course management functions
    void addCourse(const std::string& courseName, const std::string& description, int creditHours);
    bool updateCourse(const std::string& courseId, const std::string& courseName,
                     const std::string& description, int creditHours);
    bool deleteCourse(const std::string& courseId);
    Course* findCourse(const std::string& courseId); // Returns pointer
    std::vector<Course> getAllCourses() const;

    // Enrollment management functions
    bool enrollStudent(const std::string& studentId, const std::string& courseId);
    bool updateGrade(const std::string& enrollmentId, const std::string& grade);
    bool dropEnrollment(const std::string& enrollmentId);
    Enrollment* findEnrollment(const std::string& enrollmentId); // Returns pointer
    std::vector<Enrollment> getAllEnrollments() const;
    std::vector<Enrollment> getEnrollmentsForStudent(const std::string& studentId);
    std::vector<Enrollment> getEnrollmentsForCourse(const std::string& courseId);

    // Topic Management Functions
    void addTopic(const std::string& courseId, const std::string& title, const std::string& description);
    Topic* findTopic(const std::string& topicId); // Returns pointer
    bool updateTopic(const std::string& topicId, const std::string& newTitle, const std::string& newDescription);
    bool deleteTopic(const std::string& topicId);
    std::vector<Topic> getTopicsForCourse(const std::string& courseId);

    // SubTopic Management Functions
    void addSubTopic(const std::string& topicId, const std::string& title, const std::string& description);
    SubTopic* findSubTopic(const std::string& subTopicId); // Returns pointer
    bool updateSubTopic(const std::string& subTopicId, const std::string& newTitle, const std::string& newDescription);
    bool deleteSubTopic(const std::string& subTopicId);
    std::vector<SubTopic> getSubTopicsForTopic(const std::string& topicId);

    // Lesson Management Functions
    void addLesson(const std::string& subTopicId, const std::string& content);
    Lesson* findLesson(const std::string& lessonId); // Returns pointer
    bool updateLesson(const std::string& lessonId, const std::string& newContent);
    bool deleteLesson(const std::string& lessonId);
    std::vector<Lesson> getLessonsForSubTopic(const std::string& subTopicId);

    // Data persistence functions
    void saveData();
    void loadData();

    // Reports and statistics
    void displayStudentReport(const std::string& studentId);
    void displayCourseReport(const std::string& courseId);
    void displaySystemStatistics();
};

#endif // PORTAL_H
