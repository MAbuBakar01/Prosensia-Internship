#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Student {
    int id;1
    string name;
    float marks;
    char grade;
};
char calculateGrade(float marks) {
    if (marks >= 85) return 'A';
    if (marks >= 70) return 'B';
    if (marks >= 50) return 'C';
    return 'F';
}
void saveStudentRecord(const Student& student, const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << student.id << " | " << student.name << " | " 
             << student.marks << " | " << student.grade << "\n";
    }
}
void showAllRecords(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No records found.\n";
        return;
    }

    cout << "ID\tName\tMarks\tGrade\n";
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(" | ");
        size_t pos2 = line.find(" | ", pos1 + 3);
        size_t pos3 = line.find(" | ", pos2 + 3);

        string idStr = line.substr(0, pos1);
        string name = line.substr(pos1 + 3, pos2 - (pos1 + 3));
        string marksStr = line.substr(pos2 + 3, pos3 - (pos2 + 3));
        string gradeStr = line.substr(pos3 + 3);

        cout << idStr << "\t" << name << "\t" 
             << marksStr << "\t" << gradeStr << "\n";
    }
}

void findStudentByID(const string& filename, int targetID) {
    ifstream file(filename);
    bool found = false;
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(" | ");
        int currentID = stoi(line.substr(0, pos));

        if (currentID == targetID) {
            size_t pos2 = line.find(" | ", pos + 3);
            size_t pos3 = line.find(" | ", pos2 + 3);

            string name = line.substr(pos + 3, pos2 - (pos + 3));
            string marks = line.substr(pos2 + 3, pos3 - (pos2 + 3));
            string grade = line.substr(pos3 + 3);

            cout << "ID\tName\tMarks\tGrade\n";
            cout << currentID << "\t" << name << "\t" 
                 << marks << "\t" << grade << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
}
int main() {
    const string filename = "students.txt";
    int userChoice;
    do {
        cout << "\nStudent Record System\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Students\n";
        cout << "3. Find Student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        if (userChoice == 1) {
            Student newStudent;
            cout << "Enter Student ID: ";
            cin >> newStudent.id;            
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, newStudent.name);
            cout << "Enter Marks (0-100): ";
            cin >> newStudent.marks;
            if (newStudent.marks < 0 || newStudent.marks > 100) {
                cout << "Invalid marks. Please enter between 0 and 100.\n";
                continue;
            }
            newStudent.grade = calculateGrade(newStudent.marks);
            saveStudentRecord(newStudent, filename);
            cout << "Student record saved successfully.\n";
        } else if (userChoice == 2) {
            showAllRecords(filename);
        } else if (userChoice == 3) {
            int searchID;
            cout << "Enter Student ID to search: ";
            cin >> searchID;
            findStudentByID(filename, searchID);
        } else if (userChoice != 4) {
            cout << "Invalid option. Please try again.\n";
        }
    } while (userChoice != 4);
    cout << "Exiting program. Goodbye!\n";
    return 0;
}