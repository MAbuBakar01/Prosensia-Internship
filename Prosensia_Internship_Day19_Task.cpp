#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
    int rollNo;
    char name[50];
    char department[30];
    float cgpa;
public:
    void input() {
        cout << "Enter Roll No: "; cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: "; cin.getline(name, 50);
        cout << "Enter Department: "; cin.getline(department, 30);
        cout << "Enter CGPA: "; cin >> cgpa;
    }
    void display() const {
        cout << left << setw(10) << rollNo << setw(20) << name
             << setw(15) << department << setw(5) << cgpa << endl;
    }
    int getRollNo() const { return rollNo; }
    float getCGPA() const { return cgpa; }

    static void displayHeader() {
        cout << left << setw(10) << "Roll No" << setw(20) << "Name"
             << setw(15) << "Department" << setw(5) << "CGPA" << endl;
        cout << string(50, '-') << endl;
    }
};

// Add a student record
void addRecord() {
    Student s;
    s.input();
    ofstream out("students.dat", ios::binary | ios::app);
    if (!out) {
        cout << "Error opening file!\n";
        return;
    }
    out.write((char*)&s, sizeof(s));
    out.close();
    cout << "Record added successfully!\n";
}

// View all records
void viewRecords() {
    ifstream in("students.dat", ios::binary);
    if (!in) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    Student::displayHeader();
    while (in.read((char*)&s, sizeof(s))) {
        s.display();
    }
    in.close();
}

// Search for a specific student by roll number
void searchRecord(int rollNo) {
    ifstream in("students.dat", ios::binary);
    if (!in) {
        cout << "File not found.\n";
        return;
    }

    Student s;
    bool found = false;
    while (in.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            cout << "Record Found:\n";
            Student::displayHeader();
            s.display();
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found.\n";
    in.close();
}

// Update a student record
void updateRecord(int rollNo) {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    Student s;
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            cout << "Enter new details:\n";
            s.input();
            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));
            cout << "Record updated.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Record not found.\n";
    file.close();
}

// Delete a record by copying all except the one to delete
void deleteRecord(int rollNo) {
    ifstream in("students.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);
    if (!in || !out) {
        cout << "File error.\n";
        return;
    }

    Student s;
    bool found = false;
    while (in.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            found = true;
        } else {
            out.write((char*)&s, sizeof(s));
        }
    }

    in.close();
    out.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

// Sort and display students by CGPA using basic array and manual sort
void sortByCGPA() {
    ifstream in("students.dat", ios::binary);
    if (!in) {
        cout << "File not found.\n";
        return;
    }

    const int MAX = 100;
    Student students[MAX];
    int count = 0;

    while (in.read((char*)&students[count], sizeof(Student))) {
        count++;
        if (count >= MAX) break;
    }
    in.close();
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].getCGPA() < students[j + 1].getCGPA()) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
       }
        }}
    Student::displayHeader();
    for (int i = 0; i < count; i++) {
        students[i].display();    }
}
int main() {
    int choice, roll;
    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Record\n2. View Records\n3. Search Record\n4. Update Record\n5. Delete Record\n6. Sort by CGPA\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addRecord();
			 break;
            case 2: viewRecords(); 
			break;
            case 3: cout << "Enter Roll No to Search: "; 
			cin >> roll; searchRecord(roll);
			 break;
            case 4: cout << "Enter Roll No to Update: "; 
			cin >> roll; updateRecord(roll); 
			break;
            case 5: cout << "Enter Roll No to Delete: "; 
			cin >> roll; deleteRecord(roll);
			 break;
            case 6: sortByCGPA(); 
			break;
            case 0: cout << "Exiting...\n"; 
			break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
