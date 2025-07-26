#include "Portal.h"
#include <iostream> 
#include <algorithm> 

// Constructor: Loads data when a Portal object is created
Portal::Portal() {
    loadData();
}

// Generate a unique ID based on the current size of vector
std::string Portal::generateUniqueId(const std::string& prefix, int currentSize) {
    return prefix + std::to_string(currentSize + 1);
}

// Student management functions
void Portal::addStudent(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& phoneNumber) {
    std::string studentId = generateUniqueId("STU", students.size());
    Student newStudent(studentId, firstName, lastName, email, phoneNumber);
    students.push_back(newStudent);
    std::cout << "Student added successfully with ID: " << studentId << std::endl;
}

bool Portal::updateStudent(const std::string& studentId, const std::string& firstName, const std::string& lastName,
                  const std::string& email, const std::string& phoneNumber) {
    for (auto& student : students) {
        if (student.getStudentId() == studentId) {
            student.setFirstName(firstName);
            student.setLastName(lastName);
            student.setEmail(email);
            student.setPhoneNumber(phoneNumber);
            std::cout << "Student updated successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Student not found with ID: " << studentId << std::endl;
    return false;
}

bool Portal::deleteStudent(const std::string& studentId) {
    // First, remove enrollments associated with this student
    auto enroll_it = enrollments.begin();
    while (enroll_it != enrollments.end()) {
        if (enroll_it->getStudentId() == studentId) {
            enroll_it = enrollments.erase(enroll_it); // Erase and move to next
        } else {
            ++enroll_it;
        }
    }

    // Then, remove the student
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getStudentId() == studentId) {
            students.erase(students.begin() + i);
            std::cout << "Student and associated enrollments deleted successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Student not found with ID: " << studentId << std::endl;
    return false;
}

Student* Portal::findStudent(const std::string& studentId) {
    for (auto& student : students) {
        if (student.getStudentId() == studentId) {
            return &student;
        }
    }
    return nullptr;
}

std::vector<Student> Portal::getAllStudents() const {
    return students;
}

// Course management functions
void Portal::addCourse(const std::string& courseName, const std::string& description, int creditHours) {
    std::string courseId = generateUniqueId("CRS", courses.size());
    Course newCourse(courseId, courseName, description, creditHours);
    courses.push_back(newCourse);
    std::cout << "Course added successfully with ID: " << courseId << std::endl;
}

bool Portal::updateCourse(const std::string& courseId, const std::string& courseName,
                 const std::string& description, int creditHours) {
    for (auto& course : courses) {
        if (course.getCourseId() == courseId) {
            course.setCourseName(courseName);
            course.setDescription(description);
            course.setCreditHours(creditHours);
            std::cout << "Course updated successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Course not found with ID: " << courseId << std::endl;
    return false;
}

// Helper for cascading delete of topics and their children
void Portal::deleteTopicCascading(const std::string& topicId) {
    auto it_sub = subtopics_data.begin();
    while (it_sub != subtopics_data.end()) {
        if (it_sub->getTopicId() == topicId) {
            deleteSubTopicCascading(it_sub->getSubTopicId()); // Delete lessons of this subtopic
            it_sub = subtopics_data.erase(it_sub); // Delete subtopic
        } else {
            ++it_sub;
        }
    }
}

// Helper for cascading delete of subtopics and their children (lessons)
void Portal::deleteSubTopicCascading(const std::string& subTopicId) {
    auto it_les = lessons_data.begin();
    while (it_les != lessons_data.end()) {
        if (it_les->getSubTopicId() == subTopicId) {
            it_les = lessons_data.erase(it_les); // Delete lesson
        } else {
            ++it_les;
        }
    }
}


bool Portal::deleteCourse(const std::string& courseId) {
    // First, remove enrollments associated with this course
    auto enroll_it = enrollments.begin();
    while (enroll_it != enrollments.end()) {
        if (enroll_it->getCourseId() == courseId) {
            enroll_it = enrollments.erase(enroll_it);
        } else {
            ++enroll_it;
        }
    }

    // Second, remove topics (and their subtopics/lessons) associated with this course
    auto topic_it = topics_data.begin();
    while (topic_it != topics_data.end()) {
        if (topic_it->getCourseId() == courseId) {
            deleteTopicCascading(topic_it->getTopicId()); // This handles subtopics and lessons
            topic_it = topics_data.erase(topic_it); // Delete the topic itself
        } else {
            ++topic_it;
        }
    }
    
    // Then, remove the course
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i].getCourseId() == courseId) {
            courses.erase(courses.begin() + i);
            std::cout << "Course and associated enrollments, topics, subtopics, and lessons deleted successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Course not found with ID: " << courseId << std::endl;
    return false;
}


Course* Portal::findCourse(const std::string& courseId) {
    for (auto& course : courses) {
        if (course.getCourseId() == courseId) {
            return &course;
        }
    }
    return nullptr;
}

std::vector<Course> Portal::getAllCourses() const {
    return courses;
}

// Enrollment management functions
bool Portal::enrollStudent(const std::string& studentId, const std::string& courseId) {
    if (!findStudent(studentId)) {
        std::cout << "Student not found with ID: " << studentId << std::endl;
        return false;
    }
    if (!findCourse(courseId)) {
        std::cout << "Course not found with ID: " << courseId << std::endl;
        return false;
    }
    for (const auto& enrollment : enrollments) {
        if (enrollment.getStudentId() == studentId && enrollment.getCourseId() == courseId) {
            std::cout << "Student is already enrolled in this course!" << std::endl;
            return false;
        }
    }
    std::string enrollmentId = generateUniqueId("ENR", enrollments.size());
    Enrollment newEnrollment(enrollmentId, studentId, courseId);
    enrollments.push_back(newEnrollment);
    std::cout << "Student enrolled successfully with Enrollment ID: " << enrollmentId << std::endl;
    return true;
}

bool Portal::updateGrade(const std::string& enrollmentId, const std::string& grade) {
    for (auto& enrollment : enrollments) {
        if (enrollment.getEnrollmentId() == enrollmentId) {
            enrollment.setGrade(grade);
            std::cout << "Grade updated successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Enrollment not found with ID: " << enrollmentId << std::endl;
    return false;
}

bool Portal::dropEnrollment(const std::string& enrollmentId) {
    for (size_t i = 0; i < enrollments.size(); ++i) {
        if (enrollments[i].getEnrollmentId() == enrollmentId) {
            enrollments.erase(enrollments.begin() + i);
            std::cout << "Enrollment dropped successfully!" << std::endl;
            return true;
        }
    }
    std::cout << "Enrollment not found with ID: " << enrollmentId << std::endl;
    return false;
}

Enrollment* Portal::findEnrollment(const std::string& enrollmentId) {
    for (auto& enrollment : enrollments) {
        if (enrollment.getEnrollmentId() == enrollmentId) {
            return &enrollment;
        }
    }
    return nullptr;
}
std::vector<Enrollment> Portal::getAllEnrollments() const { return enrollments; }

std::vector<Enrollment> Portal::getEnrollmentsForStudent(const std::string& studentId) {
    std::vector<Enrollment> result;
    for (const auto& enrollment : enrollments) {
        if (enrollment.getStudentId() == studentId) {
            result.push_back(enrollment);
        }
    }
    return result;
}
std::vector<Enrollment> Portal::getEnrollmentsForCourse(const std::string& courseId) {
    std::vector<Enrollment> result;
    for (const auto& enrollment : enrollments) {
        if (enrollment.getCourseId() == courseId) {
            result.push_back(enrollment);
        }
    }
    return result;
}

// Topic Management Functions
void Portal::addTopic(const std::string& courseId, const std::string& title, const std::string& description) {
    if (!findCourse(courseId)) {
        std::cout << "Error: Course with ID " << courseId << " not found. Cannot add topic." << std::endl;
        return;
    }
    std::string topicId = generateUniqueId("TOP", topics_data.size());
    Topic newTopic(topicId, courseId, title, description);
    topics_data.push_back(newTopic);
    std::cout << "Topic '" << title << "' added successfully to course " << courseId << " with ID: " << topicId << std::endl;
}

Topic* Portal::findTopic(const std::string& topicId) {
    for (auto& topic : topics_data) {
        if (topic.getTopicId() == topicId) {
            return &topic;
        }
    }
    return nullptr;
}

bool Portal::updateTopic(const std::string& topicId, const std::string& newTitle, const std::string& newDescription) {
    Topic* topic = findTopic(topicId);
    if (topic) {
        topic->setTitle(newTitle);
        topic->setDescription(newDescription);
        std::cout << "Topic ID " << topicId << " updated successfully." << std::endl;
        return true;
    }
    std::cout << "Topic not found with ID: " << topicId << std::endl;
    return false;
}

bool Portal::deleteTopic(const std::string& topicId) {
    auto it = topics_data.begin();
    while (it != topics_data.end()) {
        if (it->getTopicId() == topicId) {
            deleteTopicCascading(topicId); // Delete associated subtopics and lessons
            topics_data.erase(it); // Delete the topic itself
            std::cout << "Topic ID " << topicId << " and its associated subtopics and lessons deleted successfully." << std::endl;
            return true;
        }
        ++it;
    }
    std::cout << "Topic not found with ID: " << topicId << std::endl;
    return false;
}


std::vector<Topic> Portal::getTopicsForCourse(const std::string& courseId) {
    std::vector<Topic> result;
    for (const auto& topic : topics_data) {
        if (topic.getCourseId() == courseId) {
            result.push_back(topic);
        }
    }
    return result;
}

// SubTopic Management Functions
void Portal::addSubTopic(const std::string& topicId, const std::string& title, const std::string& description) {
    if (!findTopic(topicId)) {
        std::cout << "Error: Topic with ID " << topicId << " not found. Cannot add subtopic." << std::endl;
        return;
    }
    std::string subTopicId = generateUniqueId("SUB", subtopics_data.size());
    SubTopic newSubTopic(subTopicId, topicId, title, description);
    subtopics_data.push_back(newSubTopic);
    std::cout << "SubTopic '" << title << "' added successfully to topic " << topicId << " with ID: " << subTopicId << std::endl;
}

SubTopic* Portal::findSubTopic(const std::string& subTopicId) {
    for (auto& subtopic : subtopics_data) {
        if (subtopic.getSubTopicId() == subTopicId) {
            return &subtopic;
        }
    }
    return nullptr;
}

bool Portal::updateSubTopic(const std::string& subTopicId, const std::string& newTitle, const std::string& newDescription) {
    SubTopic* subtopic = findSubTopic(subTopicId);
    if (subtopic) {
        subtopic->setTitle(newTitle);
        subtopic->setDescription(newDescription);
        std::cout << "SubTopic ID " << subTopicId << " updated successfully." << std::endl;
        return true;
    }
    std::cout << "SubTopic not found with ID: " << subTopicId << std::endl;
    return false;
}

bool Portal::deleteSubTopic(const std::string& subTopicId) {
     auto it = subtopics_data.begin();
    while (it != subtopics_data.end()) {
        if (it->getSubTopicId() == subTopicId) {
            deleteSubTopicCascading(subTopicId); // Delete associated lessons
            subtopics_data.erase(it); // Delete the subtopic itself
            std::cout << "SubTopic ID " << subTopicId << " and its associated lessons deleted successfully." << std::endl;
            return true;
        }
        ++it;
    }
    std::cout << "SubTopic not found with ID: " << subTopicId << std::endl;
    return false;
}

std::vector<SubTopic> Portal::getSubTopicsForTopic(const std::string& topicId) {
    std::vector<SubTopic> result;
    for (const auto& subtopic : subtopics_data) {
        if (subtopic.getTopicId() == topicId) {
            result.push_back(subtopic);
        }
    }
    return result;
}

// Lesson Management Functions
void Portal::addLesson(const std::string& subTopicId, const std::string& content) {
    if (!findSubTopic(subTopicId)) {
        std::cout << "Error: SubTopic with ID " << subTopicId << " not found. Cannot add lesson." << std::endl;
        return;
    }
    std::string lessonId = generateUniqueId("LES", lessons_data.size());
    Lesson newLesson(lessonId, subTopicId, content);
    lessons_data.push_back(newLesson);
    std::cout << "Lesson added successfully to subtopic " << subTopicId << " with ID: " << lessonId << std::endl;
}

Lesson* Portal::findLesson(const std::string& lessonId) {
    for (auto& lesson : lessons_data) {
        if (lesson.getLessonId() == lessonId) {
            return &lesson;
        }
    }
    return nullptr;
}

bool Portal::updateLesson(const std::string& lessonId, const std::string& newContent) {
    Lesson* lesson = findLesson(lessonId);
    if (lesson) {
        lesson->setContent(newContent);
        std::cout << "Lesson ID " << lessonId << " updated successfully." << std::endl;
        return true;
    }
    std::cout << "Lesson not found with ID: " << lessonId << std::endl;
    return false;
}

bool Portal::deleteLesson(const std::string& lessonId) {
    for (size_t i = 0; i < lessons_data.size(); ++i) {
        if (lessons_data[i].getLessonId() == lessonId) {
            lessons_data.erase(lessons_data.begin() + i);
            std::cout << "Lesson ID " << lessonId << " deleted successfully." << std::endl;
            return true;
        }
    }
    std::cout << "Lesson not found with ID: " << lessonId << std::endl;
    return false;
}

std::vector<Lesson> Portal::getLessonsForSubTopic(const std::string& subTopicId) {
    std::vector<Lesson> result;
    for (const auto& lesson : lessons_data) {
        if (lesson.getSubTopicId() == subTopicId) {
            result.push_back(lesson);
        }
    }
    return result;
}


// Data persistence functions
void Portal::saveData() {
    // Save students
    std::ofstream studentsFile(STUDENTS_FILE);
    if (studentsFile.is_open()) {
        for (const auto& student : students) {
            studentsFile << student.getStudentId() << "," << student.getFirstName() << ","
                         << student.getLastName() << "," << student.getEmail() << ","
                         << student.getPhoneNumber() << "," << student.getRegistrationDate() << std::endl;
        }
        studentsFile.close();
    } else {
        std::cout << "Unable to open file for saving students!" << std::endl;
    }

    // Save courses
    std::ofstream coursesFile(COURSES_FILE);
    if (coursesFile.is_open()) {
        for (const auto& course : courses) {
            coursesFile << course.getCourseId() << ","
                        << course.getCourseName() << ","
                        << course.getDescription() << ","
                        << course.getCreditHours() << std::endl;
        }
        coursesFile.close();
    } else {
        std::cout << "Unable to open file for saving courses!" << std::endl;
    }

    // Save enrollments
    std::ofstream enrollmentsFile(ENROLLMENTS_FILE);
    if (enrollmentsFile.is_open()) {
        for (const auto& enrollment : enrollments) {
            enrollmentsFile << enrollment.getEnrollmentId() << ","
                            << enrollment.getStudentId() << ","
                            << enrollment.getCourseId() << ","
                            << enrollment.getEnrollmentDate() << ","
                            << enrollment.getGrade() << std::endl;
        }
        enrollmentsFile.close();
    } else {
        std::cout << "Unable to open file for saving enrollments!" << std::endl;
    }

    // Save Topics
    std::ofstream topicsFile(TOPICS_FILE);
    if (topicsFile.is_open()) {
        for (const auto& topic : topics_data) {
            topicsFile << topic.getTopicId() << ","
                       << topic.getCourseId() << ","
                       << topic.getTitle() << ","
                       << topic.getDescription() << std::endl;
        }
        topicsFile.close();
    } else {
        std::cout << "Unable to open file for saving topics!" << std::endl;
    }

    // Save SubTopics
    std::ofstream subTopicsFile(SUBTOPICS_FILE);
    if (subTopicsFile.is_open()) {
        for (const auto& subtopic : subtopics_data) {
            subTopicsFile << subtopic.getSubTopicId() << ","
                          << subtopic.getTopicId() << ","
                          << subtopic.getTitle() << ","
                          << subtopic.getDescription() << std::endl;
        }
        subTopicsFile.close();
    } else {
        std::cout << "Unable to open file for saving subtopics!" << std::endl;
    }

    // Save Lessons
    std::ofstream lessonsFile(LESSONS_FILE);
    if (lessonsFile.is_open()) {
        for (const auto& lesson : lessons_data) {
            std::string processed_content = lesson.getContent();
            size_t pos = 0;
            // Replace actual newline characters with "\n" literal string for CSV storage
            while ((pos = processed_content.find('\n', pos)) != std::string::npos) {
                processed_content.replace(pos, 1, "\\n");
                pos += 2; // Move past the inserted "\\n"
            }
            lessonsFile << lesson.getLessonId() << ","
                        << lesson.getSubTopicId() << ","
                        << processed_content << std::endl;
        }
        lessonsFile.close();
    } else {
        std::cout << "Unable to open file for saving lessons!" << std::endl;
    }
}

void Portal::loadData() {
    std::string line, token;
    size_t pos;

    // Load students
    std::ifstream studentsFile(STUDENTS_FILE);
    if (studentsFile.is_open()) {
        students.clear();
        while (getline(studentsFile, line)) {
            if (line.empty()) continue;
            std::vector<std::string> tokens;
            std::string current_token;
            for(int i=0; i<5; ++i){ // Expect 5 commas for 6 fields
                pos = line.find(",");
                if(pos == std::string::npos && i < 5) {tokens.clear(); break;} // Malformed line
                current_token = line.substr(0, pos);
                tokens.push_back(current_token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // The rest is the last token

            if (tokens.size() == 6) {
                Student student(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
                student.setRegistrationDate(tokens[5]);
                students.push_back(student);
            }
        }
        studentsFile.close();
    }

    // Load courses
    std::ifstream coursesFile(COURSES_FILE);
    if (coursesFile.is_open()) {
        courses.clear();
        while (getline(coursesFile, line)) {
            if (line.empty()) continue;
            std::vector<std::string> tokens;
            std::string current_token;
            for(int i=0; i<3; ++i){ // Expect 3 commas for 4 fields
                pos = line.find(",");
                 if(pos == std::string::npos && i < 3) {tokens.clear(); break;}
                current_token = line.substr(0, pos);
                tokens.push_back(current_token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 4) {
                int credits = 0;
                try {
                    credits = std::stoi(tokens[3]);
                } catch (const std::exception& e) {
                    std::cerr << "Error converting credit hours for course " << tokens[0] << ": " << e.what() << std::endl;
                }
                Course course(tokens[0], tokens[1], tokens[2], credits);
                courses.push_back(course);
            }
        }
        coursesFile.close();
    }

    // Load enrollments
    std::ifstream enrollmentsFile(ENROLLMENTS_FILE);
    if (enrollmentsFile.is_open()) {
        enrollments.clear();
        while (getline(enrollmentsFile, line)) {
            if (line.empty()) continue;
            std::vector<std::string> tokens;
            std::string current_token;
            for(int i=0; i<4; ++i){ // Expect 4 commas for 5 fields
                pos = line.find(",");
                if(pos == std::string::npos && i < 4) {tokens.clear(); break;}
                current_token = line.substr(0, pos);
                tokens.push_back(current_token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 5) {
                Enrollment enrollment(tokens[0], tokens[1], tokens[2]);
                enrollment.setEnrollmentDate(tokens[3]);
                enrollment.setGrade(tokens[4]);
                enrollments.push_back(enrollment);
            }
        }
        enrollmentsFile.close();
    }

    // Load Topics
    std::ifstream topicsFile(TOPICS_FILE);
    if (topicsFile.is_open()) {
        topics_data.clear();
        while (getline(topicsFile, line)) {
            if (line.empty()) continue;
            std::vector<std::string> tokens;
            std::string current_token;
            for(int i=0; i<3; ++i){ // Expect 3 commas for 4 fields
                pos = line.find(",");
                if(pos == std::string::npos && i < 3) {tokens.clear(); break;}
                current_token = line.substr(0, pos);
                tokens.push_back(current_token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 4) {
                Topic topic(tokens[0], tokens[1], tokens[2], tokens[3]);
                topics_data.push_back(topic);
            }
        }
        topicsFile.close();
    }

    // Load SubTopics
    std::ifstream subTopicsFile(SUBTOPICS_FILE);
    if (subTopicsFile.is_open()) {
        subtopics_data.clear();
        while (getline(subTopicsFile, line)) {
            if (line.empty()) continue;
            std::vector<std::string> tokens;
            std::string current_token;
            for(int i=0; i<3; ++i){ // Expect 3 commas for 4 fields
                pos = line.find(",");
                if(pos == std::string::npos && i < 3) {tokens.clear(); break;}
                current_token = line.substr(0, pos);
                tokens.push_back(current_token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 4) {
                SubTopic subtopic(tokens[0], tokens[1], tokens[2], tokens[3]);
                subtopics_data.push_back(subtopic);
            }
        }
        subTopicsFile.close();
    }

    // Load Lessons
    std::ifstream lessonsFile(LESSONS_FILE);
    if (lessonsFile.is_open()) {
        lessons_data.clear();
        while (getline(lessonsFile, line)) {
            if (line.empty()) continue;
            std::vector<std::string> tokens;
            std::string current_token;
             for(int i=0; i<2; ++i){ // Expect 2 commas for 3 fields
                pos = line.find(",");
                if(pos == std::string::npos && i < 2) {tokens.clear(); break;}
                current_token = line.substr(0, pos);
                tokens.push_back(current_token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // The rest is the content

            if (tokens.size() == 3) {
                std::string loaded_content = tokens[2];
                size_t replace_pos = 0;
                // Replace "\\n" literal string back to actual newline characters
                while ((replace_pos = loaded_content.find("\\n", replace_pos)) != std::string::npos) {
                    loaded_content.replace(replace_pos, 2, "\n");
                    replace_pos += 1; // Move past the replaced '\n'
                }
                Lesson lesson(tokens[0], tokens[1], loaded_content);
                lessons_data.push_back(lesson);
            }
        }
        lessonsFile.close();
    }
}


// Reports and statistics
void Portal::displayStudentReport(const std::string& studentId) {
    Student* student = findStudent(studentId);
    if (!student) {
        std::cout << "Student not found with ID: " << studentId << std::endl;
        return;
    }

    std::cout << "\n===== STUDENT REPORT =====" << std::endl;
    std::cout << "ID: " << student->getStudentId() << std::endl;
    std::cout << "Name: " << student->getFullName() << std::endl;
    std::cout << "Email: " << student->getEmail() << std::endl;
    std::cout << "Phone: " << student->getPhoneNumber() << std::endl;
    std::cout << "Registration Date: " << student->getRegistrationDate() << std::endl;

    std::vector<Enrollment> studentEnrollments = getEnrollmentsForStudent(studentId);
    std::cout << "\nEnrolled Courses: " << studentEnrollments.size() << std::endl;

    if (studentEnrollments.empty()) {
        std::cout << "No enrolled courses." << std::endl;
    } else {
        std::cout << "------------------------------" << std::endl;
        std::cout << "Course ID | Course Name | Credits | Grade" << std::endl;
        std::cout << "------------------------------" << std::endl;

        int totalCredits = 0;
        for (const auto& enrollment : studentEnrollments) {
            Course* course = findCourse(enrollment.getCourseId());
            if (course) {
                std::cout << course->getCourseId() << " | "
                     << course->getCourseName() << " | "
                     << course->getCreditHours() << " | "
                     << enrollment.getGrade() << std::endl;
                totalCredits += course->getCreditHours();
            }
        }
        std::cout << "------------------------------" << std::endl;
        std::cout << "Total Credits: " << totalCredits << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

void Portal::displayCourseReport(const std::string& courseId) {
    Course* course = findCourse(courseId);
    if (!course) {
        std::cout << "Course not found with ID: " << courseId << std::endl;
        return;
    }
    std::cout << "\n===== COURSE REPORT =====" << std::endl;
    std::cout << "ID: " << course->getCourseId() << std::endl;
    std::cout << "Name: " << course->getCourseName() << std::endl;
    std::cout << "Description: " << course->getDescription() << std::endl;
    std::cout << "Credit Hours: " << course->getCreditHours() << std::endl;

    std::vector<Enrollment> courseEnrollments = getEnrollmentsForCourse(courseId);
    std::cout << "\nEnrolled Students: " << courseEnrollments.size() << std::endl;

    if (courseEnrollments.empty()) {
        std::cout << "No enrolled students." << std::endl;
    } else {
        std::cout << "------------------------------" << std::endl;
        std::cout << "Student ID | Student Name | Grade" << std::endl;
        std::cout << "------------------------------" << std::endl;

        for (const auto& enrollment : courseEnrollments) {
            Student* student = findStudent(enrollment.getStudentId());
            if (student) {
                std::cout << student->getStudentId() << " | "
                     << student->getFullName() << " | "
                     << enrollment.getGrade() << std::endl;
            }
        }
        std::cout << "------------------------------" << std::endl;
    }
    std::vector<Topic> topicsInCourse = getTopicsForCourse(courseId);
    std::cout << "\nTopics in this Course: " << topicsInCourse.size() << std::endl;
    if (topicsInCourse.empty()) {
        std::cout << "No topics in this course." << std::endl;
    } else {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Topic ID | Title | Description" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        for (const auto& topic : topicsInCourse) {
            std::cout << topic.getTopicId() << " | " << topic.getTitle() << " | " << topic.getDescription() << std::endl;
        }
        std::cout << "--------------------------------------------------" << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

void Portal::displaySystemStatistics() {
    std::cout << "\n===== SYSTEM STATISTICS =====" << std::endl;
    std::cout << "Total Students: " << students.size() << std::endl;
    std::cout << "Total Courses: " << courses.size() << std::endl;
    std::cout << "Total Enrollments: " << enrollments.size() << std::endl;
    std::cout << "Total Topics: " << topics_data.size() << std::endl;
    std::cout << "Total SubTopics: " << subtopics_data.size() << std::endl;
    std::cout << "Total Lessons: " << lessons_data.size() << std::endl;

    int totalCreditHours = 0;
    for (const auto& course : courses) {
        totalCreditHours += course.getCreditHours();
    }
    std::cout << "Total Credit Hours Available: " << totalCreditHours << std::endl;
    std::cout << "=========================" << std::endl;
}
