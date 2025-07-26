#include <iostream>
#include <vector>
#include <string>
#include <limits> 

#include "Portal.h"
#include "Student.h" 
#include "Course.h"  
#include "Enrollment.h" 
#include "ContentHierarchy.h" 
#include "Utility.h" 

using namespace std; 

// Forward declarations for menu functions (definitions below main)
void displayMainMenu();
void displayStudentMenu();
void displayCourseMenu();
void displayEnrollmentMenu();
void displayReportMenu();
void manageCourseContent(Portal& manager);
void manageTopicsMenu(Portal& manager, const string& courseId);
void manageSubTopicsMenu(Portal& manager, const string& topicId);
void manageLessonsMenu(Portal& manager, const string& subTopicId);


//-------------------------------Main Function--------------------------------------------
int main() {
    Portal manager; // Portal constructor calls loadData()
    int choice, subChoice;
    string studentId, courseId, enrollmentId;
    string firstName, lastName, email, phoneNumber;
    string courseName, description, grade;
    string title, content; // For topics, lessons etc.
    int creditHours;

    while (true) {
        displayMainMenu();
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line after reading integer

   switch (choice) {
          case 1: // Student Management
               do {
                   displayStudentMenu();
                    cin >> subChoice;
                     if (cin.fail()) {
                        cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     cout << "Invalid input. Please enter a number." << endl;
                        subChoice = 0; // Force loop to continue or re-prompt
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

              switch (subChoice) {
                        case 1: // Add New Student
                            do {
                                cout << "Enter First Name: ";
                     getline(cin, firstName);
                            if (!isValidName(firstName)) {
           cout << "Invalid first name. Please use characters and spaces only, and ensure it's not empty." << endl;
                                }
                            } while (!isValidName(firstName));

                            do {
                                cout << "Enter Last Name: ";
     
	                   getline(cin, lastName);
                     if (!isValidName(lastName)) {
                                    cout << "Invalid last name. Please use characters and spaces only, and ensure it's not empty." << endl;
                                }
                            } while (!isValidName(lastName));

                            do {
                                cout << "Enter Email: ";
                                getline(cin, email);
                                if (!isValidEmail(email)) {
                                    cout << "Invalid email format. Ensure it contains '@' and a '.' after it (e.g., user@example.com)." << endl;
                                }
                            } while (!isValidEmail(email));

                            do {
                                cout << "Enter Phone Number (digits only): ";
                                getline(cin, phoneNumber);
                                if (!isValidPhoneNumber(phoneNumber)) {
                                    cout << "Invalid phone number. Please use digits only." << endl;
                                }
                            } while (!isValidPhoneNumber(phoneNumber));

                            manager.addStudent(firstName, lastName, email, phoneNumber);
                            break;
                        case 2: // Update Student
                            cout << "Enter Student ID to update: ";
                            getline(cin, studentId);
                            if (manager.findStudent(studentId)) {
                                do {
                                    cout << "Enter New First Name: ";
                                    getline(cin, firstName);
                                    if (!isValidName(firstName)) {
                                        cout << "Invalid first name. Please use characters and spaces only, and ensure it's not empty." << endl;
                                    }
                                } while (!isValidName(firstName));

                                do {
                                    cout << "Enter New Last Name: ";
                                    getline(cin, lastName);
                                    if (!isValidName(lastName)) {
                                        cout << "Invalid last name. Please use characters and spaces only, and ensure it's not empty." << endl;
                                    }
                                } while (!isValidName(lastName));

                                do {
                                    cout << "Enter New Email: ";
                                    getline(cin, email);
                                    if (!isValidEmail(email)) {
                                        cout << "Invalid email format. Ensure it contains '@' and a '.' after it (e.g., user@example.com)." << endl;
                                    }
                                } while (!isValidEmail(email));

                                do {
                                    cout << "Enter New Phone Number (digits only): ";
                                    getline(cin, phoneNumber);
                                    if (!isValidPhoneNumber(phoneNumber)) {
                                        cout << "Invalid phone number. Please use digits only." << endl;
                                    }
                                } while (!isValidPhoneNumber(phoneNumber));
                                manager.updateStudent(studentId, firstName, lastName, email, phoneNumber);
                            } else {
                                cout << "Student not found with ID: " << studentId << endl;
                            }
                            break;
                        case 3: // Delete Student
                            cout << "Enter Student ID: ";
                            getline(cin, studentId);
                            manager.deleteStudent(studentId);
                            break;
                        case 4: // View All Students
                            cout << "\n===== ALL STUDENTS =====" << endl;
                            cout << "ID    |Name             |Email             |Phone             |Registered Date" << endl;
                            cout << "-----------------------------------------------------------------------------" << endl;
                            for (const auto& student : manager.getAllStudents()) {
                                cout << student.getStudentId() << " | "
                                     << student.getFullName() << " | "
                                     << student.getEmail() << " | "
                                     << student.getPhoneNumber() << " | "
                                     << student.getRegistrationDate() << endl;
                            }
                            cout << "-----------------------------------------------------------------------------" << endl;
                            cout << "Total Students: " << manager.getAllStudents().size() << endl;
                            break;
                        case 5: // Find Student
                          {
                            cout << "Enter Student ID: ";
                            getline(cin, studentId);
                            Student* foundStudent = manager.findStudent(studentId);
                            if (foundStudent) {
                                cout << "\n===== STUDENT DETAILS =====" << endl;
                                cout << "ID: " << foundStudent->getStudentId() << endl;
                                cout << "Name: " << foundStudent->getFullName() << endl;
                                cout << "Email: " << foundStudent->getEmail() << endl;
                                cout << "Phone: " << foundStudent->getPhoneNumber() << endl;
                                cout << "Registration Date: " << foundStudent->getRegistrationDate() << endl;
                            } else {
                                cout << "Student not found with ID: " << studentId << endl;
                            }
                            break;
                          }
                        case 6: // Back to Main Menu
                           break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (subChoice != 6);
                break;
            case 2: // Course Management & Content
                do {
                    displayCourseMenu();
                    cin >> subChoice;
                     if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number." << endl;
                        subChoice = 0;
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (subChoice) {
                        case 1: // Add New Course
                            cout << "Enter Course Name: ";
                            getline(cin, courseName);
                            cout << "Enter Description: ";
                            getline(cin, description);
                            cout << "Enter Credit Hours: ";
                            cin >> creditHours;
                             if (cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid input for credit hours." << endl;
                                break;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            manager.addCourse(courseName, description, creditHours);
                            break;
                        case 2: // Update Course
                            cout << "Enter Course ID: ";
                            getline(cin, courseId);
                            if (manager.findCourse(courseId)) {
                                cout << "Enter New Course Name: ";
                                getline(cin, courseName);
                                cout << "Enter New Description: ";
                                getline(cin, description);
                                cout << "Enter New Credit Hours: ";
                                cin >> creditHours;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Invalid input for credit hours." << endl;
                                    break;
                                }
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                manager.updateCourse(courseId, courseName, description, creditHours);
                            } else {
                                cout << "Course not found with ID: " << courseId << endl;
                            }
                            break;
                        case 3: // Delete Course
                            cout << "Enter Course ID: ";
                            getline(cin, courseId);
                            manager.deleteCourse(courseId);
                            break;
                        case 4: // View All Courses
                            cout << "\n===== ALL COURSES =====" << endl;
                            cout << "ID | Name | Credits | Description" << endl;
                            cout << "--------------------------------------------------" << endl;
                            for (const auto& course : manager.getAllCourses()) {
                                cout << course.getCourseId() << " | "
                                     << course.getCourseName() << " | "
                                     << course.getCreditHours() << " | "
                                     << course.getDescription() << endl;
                            }
                            cout << "--------------------------------------------------" << endl;
                            cout << "Total Courses: " << manager.getAllCourses().size() << endl;
                            break;
                        case 5: // Find Course
                           {
                            cout << "Enter Course ID: ";
                            getline(cin, courseId);
                            Course* foundCourse = manager.findCourse(courseId);
                            if (foundCourse) {
                                cout << "\n===== COURSE DETAILS =====" << endl;
                                cout << "ID: " << foundCourse->getCourseId() << endl;
                                cout << "Name: " << foundCourse->getCourseName() << endl;
                                cout << "Description: " << foundCourse->getDescription() << endl;
                                cout << "Credit Hours: " << foundCourse->getCreditHours() << endl;
                                vector<Topic> topics = manager.getTopicsForCourse(courseId);
                                cout << "--- Topics (" << topics.size() << ") ---" << endl;
                                if(topics.empty()){ cout << "No topics yet." << endl;}
                                for(const auto& t : topics){
                                    cout << "  ID: " << t.getTopicId() << ", Title: " << t.getTitle() << endl;
                                }

                            } else {
                                cout << "Course not found with ID: " << courseId << endl;
                            }
                            break;
                           }
                        case 6: // Manage Content for a Course
                            manageCourseContent(manager);
                            break;
                        case 7: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (subChoice != 7);
                break;
            case 3: // Enrollment Management
                do {
                    displayEnrollmentMenu();
                    cin >> subChoice;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number." << endl;
                        subChoice = 0;
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (subChoice) {
                        case 1: // Enroll Student in Course
                            cout << "Enter Student ID: ";
                            getline(cin, studentId);
                            cout << "Enter Course ID: ";
                            getline(cin, courseId);
                            manager.enrollStudent(studentId, courseId);
                            break;
                        case 2: { // Update Grade
                            cout << "Enter Enrollment ID: ";
                            getline(cin, enrollmentId);
                            Enrollment* foundEnrollment = manager.findEnrollment(enrollmentId);
                            if (foundEnrollment) {
                                cout << "Current Grade: " << foundEnrollment->getGrade() << endl;
                                cout << "Enter New Grade: ";
                                getline(cin, grade);
                                manager.updateGrade(enrollmentId, grade);
                            } else {
                                cout << "Enrollment not found with ID: " << enrollmentId << endl;
                            }
                            break;
                        }
                        case 3: { // Drop Enrollment
                            cout << "Enter Enrollment ID: ";
                            getline(cin, enrollmentId);
                            manager.dropEnrollment(enrollmentId);
                            break;
                        }
                        case 4: // View All Enrollments
                            cout << "\n===== ALL ENROLLMENTS =====" << endl;
                            cout << "ID | Student Name | Course Name | Date | Grade" << endl;
                            cout << "------------------------------------------------------------" << endl;
                            for (const auto& enrollment : manager.getAllEnrollments()) {
                                Student* student = manager.findStudent(enrollment.getStudentId());
                                Course* course_ptr = manager.findCourse(enrollment.getCourseId());
                                string studentName = student ? student->getFullName() : "Unknown Student";
                                string courseNameStr = course_ptr ? course_ptr->getCourseName() : "Unknown Course";
                                cout << enrollment.getEnrollmentId() << " | "
                                     << studentName << " | "
                                     << courseNameStr << " | "
                                     << enrollment.getEnrollmentDate() << " | "
                                     << enrollment.getGrade() << endl;
                            }
                            cout << "------------------------------------------------------------" << endl;
                            cout << "Total Enrollments: " << manager.getAllEnrollments().size() << endl;
                            break;
                        case 5: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (subChoice != 5);
                break;
            case 4: // Reports
                do {
                    displayReportMenu();
                    cin >> subChoice;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number." << endl;
                        subChoice = 0;
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (subChoice) {
                        case 1: // Student Report
                            cout << "Enter Student ID: ";
                            getline(cin, studentId);
                            manager.displayStudentReport(studentId);
                            break;
                        case 2: // Course Report
                            cout << "Enter Course ID: ";
                            getline(cin, courseId);
                            manager.displayCourseReport(courseId);
                            break;
                        case 3: // System Statistics
                            manager.displaySystemStatistics();
                            break;
                        case 4: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (subChoice != 4);
                break;
            case 5: // Save Data
                cout << "Saving all data..." << endl;
                manager.saveData();
                cout << "Data saved successfully." << endl;
                break;
            case 6: // Exit
                cout << "Saving data and exiting program..." << endl;
                manager.saveData(); // Save data before exiting
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
  return 0; // Should not be reached due to infinite loop and exit condition
}

// -------------Menu display function definitions-------------
void displayMainMenu() {
    cout << "\n===== TOPIC BASED CONTENT MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Student Management" << endl;
    cout << "2. Course Management & Content" << endl;
    cout << "3. Enrollment Management" << endl;
    cout << "4. Reports" << endl;
    cout << "5. Save All Data" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice (1-6): ";
}

void displayStudentMenu() {
    cout << "\n===== STUDENT MANAGEMENT =====" << endl;
    cout << "1. Add New Student" << endl;
    cout << "2. Update Student" << endl;
    cout << "3. Delete Student" << endl;
    cout << "4. View All Students" << endl;
    cout << "5. Find Student" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "Enter your choice (1-6): ";
}

void displayCourseMenu() {
    cout << "\n===== COURSE MANAGEMENT & CONTENT =====" << endl;
    cout << "1. Add New Course" << endl;
    cout << "2. Update Course Details" << endl;
    cout << "3. Delete Course" << endl;
    cout << "4. View All Courses" << endl;
    cout << "5. Find Course & View Details" << endl;
    cout << "6. Manage Content for a Course (Topics, Subtopics, Lessons)" << endl;
    cout << "7. Back to Main Menu" << endl;
    cout << "Enter your choice (1-7): ";
}

void manageCourseContent(Portal& manager) {
    string courseId;
    cout << "Enter Course ID to manage its content: ";
    getline(cin, courseId);
    Course* course = manager.findCourse(courseId);
    if (!course) {
        cout << "Course not found with ID: " << courseId << endl;
        return;
    }
    cout << "Managing content for Course: " << course->getCourseName() << " (ID: " << courseId << ")" << endl;
    manageTopicsMenu(manager, courseId);
}


void manageLessonsMenu(Portal& manager, const string& subTopicId) {
    int choice;
    string lessonId, content;

    SubTopic* subTopic = manager.findSubTopic(subTopicId);
     if (!subTopic) {
        cout << "Error: SubTopic " << subTopicId << " not found." << endl;
        return;
    }

    do {
        cout << "\n--- LESSON MANAGEMENT for SubTopic: " << subTopic->getTitle() << " (ID: " << subTopicId << ") ---" << endl;
        cout << "1. Add Lesson" << endl;
        cout << "2. View Lessons" << endl;
        cout << "3. Update Lesson" << endl;
        cout << "4. Delete Lesson" << endl;
        cout << "5. Back to SubTopic Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0; // Reset choice
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Important after reading int

        switch (choice) {
            case 1:
                cout << "Enter Lesson Content (use \\n for newlines in input if desired, will be stored as actual newlines): ";
                getline(cin, content);
                manager.addLesson(subTopicId, content);
                break;
            case 2: {
                cout << "\n--- Lessons for SubTopic: " << subTopic->getTitle() << " (ID: " << subTopicId << ") ---" << endl;
                vector<Lesson> lessons = manager.getLessonsForSubTopic(subTopicId);
                if (lessons.empty()) {
                    cout << "No lessons found for this subtopic." << endl;
                } else {
                    cout << "ID | Content Preview" << endl;
                    cout << "-----------------------------------" << endl;
                    for (const auto& l : lessons) {
                        string preview = l.getContent();
                        // Replace newlines with spaces for single-line preview
                        size_t pos_nl = 0;
                        while((pos_nl = preview.find('\n', pos_nl)) != string::npos){
                            preview.replace(pos_nl, 1, " ");
                        }
                        if (preview.length() > 30) preview = preview.substr(0, 27) + "...";
                        cout << l.getLessonId() << " | " << preview << endl;
                    }
                    cout << "-----------------------------------" << endl;
                    cout << "To see full content, use update/find lesson option or view via reports." << endl;
                }
                break;
            }
            case 3:
                cout << "Enter Lesson ID to update: ";
                getline(cin, lessonId);
                if(manager.findLesson(lessonId)){
                    cout << "Enter new Lesson Content: ";
                    getline(cin, content);
                    manager.updateLesson(lessonId, content);
                } else {
                    cout << "Lesson with ID " << lessonId << " not found." << endl;
                }
                break;
            case 4:
                cout << "Enter Lesson ID to delete: ";
                getline(cin, lessonId);
                manager.deleteLesson(lessonId);
                break;
            case 5:
                cout << "Returning to SubTopic Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

void manageSubTopicsMenu(Portal& manager, const string& topicId) {
    int choice;
    string subTopicId, title, description;
    Topic* topic = manager.findTopic(topicId);
    if(!topic){
        cout << "Error: Topic " << topicId << " not found." << endl;
        return;
    }

    do {
        cout << "\n--- SUBTOPIC MANAGEMENT for Topic: " << topic->getTitle() << " (ID: " << topicId << ") ---" << endl;
        cout << "1. Add SubTopic" << endl;
        cout << "2. View SubTopics" << endl;
        cout << "3. Update SubTopic" << endl;
        cout << "4. Delete SubTopic" << endl;
        cout << "5. Manage Lessons for a SubTopic" << endl;
        cout << "6. Back to Topic Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter SubTopic Title: ";
                getline(cin, title);
                cout << "Enter SubTopic Description: ";
                getline(cin, description);
                manager.addSubTopic(topicId, title, description);
                break;
            case 2: {
                cout << "\n--- SubTopics for Topic: " << topic->getTitle() << " (ID: " << topicId << ") ---" << endl;
                vector<SubTopic> subtopics = manager.getSubTopicsForTopic(topicId);
                if (subtopics.empty()) {
                    cout << "No subtopics found for this topic." << endl;
                } else {
                    cout << "ID | Title | Description" << endl;
                    cout << "-----------------------------------" << endl;
                    for (const auto& st : subtopics) {
                        cout << st.getSubTopicId() << " | " << st.getTitle() << " | " << st.getDescription() << endl;
                    }
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 3:
                cout << "Enter SubTopic ID to update: ";
                getline(cin, subTopicId);
                 if(manager.findSubTopic(subTopicId)){
                    cout << "Enter new SubTopic Title: ";
                    getline(cin, title);
                    cout << "Enter new SubTopic Description: ";
                    getline(cin, description);
                    manager.updateSubTopic(subTopicId, title, description);
                } else {
                     cout << "SubTopic with ID " << subTopicId << " not found." << endl;
                 }
                break;
            case 4:
                cout << "Enter SubTopic ID to delete: ";
                getline(cin, subTopicId);
                manager.deleteSubTopic(subTopicId);
                break;
            case 5:
                cout << "Enter SubTopic ID to manage its lessons: ";
                getline(cin, subTopicId);
                if (manager.findSubTopic(subTopicId)) {
                    manageLessonsMenu(manager, subTopicId);
                } else {
                    cout << "SubTopic not found with ID: " << subTopicId << endl;
                }
                break;
            case 6:
                cout << "Returning to Topic Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void manageTopicsMenu(Portal& manager, const string& courseId) {
    int choice;
    string topicId, title, description;
    Course* course = manager.findCourse(courseId);
     if(!course){
        cout << "Error: Course " << courseId << " not found." << endl;
        return;
    }

    do {
        cout << "\n--- TOPIC MANAGEMENT for Course: " << course->getCourseName() << " (ID: " << courseId << ") ---" << endl;
        cout << "1. Add Topic" << endl;
        cout << "2. View Topics" << endl;
        cout << "3. Update Topic" << endl;
        cout << "4. Delete Topic" << endl;
        cout << "5. Manage SubTopics for a Topic" << endl;
        cout << "6. Back to Course Management Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter Topic Title: ";
                getline(cin, title);
                cout << "Enter Topic Description: ";
                getline(cin, description);
                manager.addTopic(courseId, title, description);
                break;
            case 2: {
                cout << "\n--- Topics for Course: " << course->getCourseName() << " (ID: " << courseId << ") ---" << endl;
                vector<Topic> topics = manager.getTopicsForCourse(courseId);
                if (topics.empty()) {
                    cout << "No topics found for this course." << endl;
                } else {
                    cout << "ID | Title | Description" << endl;
                    cout << "-----------------------------------" << endl;
                    for (const auto& t : topics) {
                        cout << t.getTopicId() << " | " << t.getTitle() << " | " << t.getDescription() << endl;
                    }
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 3:
                cout << "Enter Topic ID to update: ";
                getline(cin, topicId);
                if(manager.findTopic(topicId)){
                    cout << "Enter new Topic Title: ";
                    getline(cin, title);
                    cout << "Enter new Topic Description: ";
                    getline(cin, description);
                    manager.updateTopic(topicId, title, description);
                } else {
                     cout << "Topic with ID " << topicId << " not found." << endl;
                }
                break;
            case 4:
                cout << "Enter Topic ID to delete: ";
                getline(cin, topicId);
                manager.deleteTopic(topicId);
                break;
            case 5:
                cout << "Enter Topic ID to manage its subtopics: ";
                getline(cin, topicId);
                if (manager.findTopic(topicId)) {
                    manageSubTopicsMenu(manager, topicId);
                } else {
                    cout << "Topic not found with ID: " << topicId << endl;
                }
                break;
            case 6:
                cout << "Returning to Course Management Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}


void displayEnrollmentMenu() {
    cout << "\n===== ENROLLMENT MANAGEMENT =====" << endl;
    cout << "1. Enroll Student in Course" << endl;
    cout << "2. Update Grade" << endl;
    cout << "3. Drop Enrollment" << endl;
    cout << "4. View All Enrollments" << endl;
    cout << "5. Back to Main Menu" << endl;
    cout << "Enter your choice (1-5): ";
}

void displayReportMenu() {
    cout << "\n===== REPORTS =====" << endl;
    cout << "1. Student Report" << endl;
    cout << "2. Course Report (includes topics)" << endl;
    cout << "3. System Statistics" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Enter your choice (1-4): ";
}
