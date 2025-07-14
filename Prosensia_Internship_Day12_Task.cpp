#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

const int MAX_EMPLOYEES=100;

struct Employee{
    int id;
    string name;
    string department;
    double salary;
};

void loadFromFile(Employee employees[],int& count,const string& filename);
void saveToFile(Employee employees[],int count,const string& filename);
void addEmployee(Employee employees[],int& count);
void viewEmployees(const Employee employees[],int count);
void updateSalary(Employee employees[],int count,int id);
void calculateSalaryStats(const Employee employees[],int count);
void logAction(const string& message);

int main(){
    Employee employees[MAX_EMPLOYEES];
    int employeeCount=0;
    string dataFile="employees.txt";
    loadFromFile(employees,employeeCount,dataFile);
    int choice;
    do{
        cout<<endl<<"=== Employee Record Management ==="<<endl;
        cout<<"1. Add Employee"<<endl;
        cout<<"2. View All Employees"<<endl;
        cout<<"3. Update Salary"<<endl;
        cout<<"4. Salary Statistics"<<endl;
        cout<<"5. Save & Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                addEmployee(employees,employeeCount);
                break;
            case 2:
                viewEmployees(employees,employeeCount);
                break;
            case 3:{
                int id;
                cout<<"Enter ID to update salary: ";
                cin>>id;
                updateSalary(employees,employeeCount,id);
                break;
            }
            case 4:
                calculateSalaryStats(employees,employeeCount);
                break;
            case 5:
                saveToFile(employees,employeeCount,dataFile);
                cout<<"Data saved. Exiting..."<<endl;
                break;
            default:
                cout<<"Invalid option! Try again."<<endl;
        }
    }while(choice!=5);

    return 0;
}

void loadFromFile(Employee employees[],int& count,const string& filename){
    ifstream file(filename);
    if(!file.is_open())return;

    while(file>>employees[count].id){
        file.ignore();
        getline(file,employees[count].name,',');
        getline(file,employees[count].department,',');
        file>>employees[count].salary;
        file.ignore();
        count++;
    }
    file.close();
}
void saveToFile(Employee employees[],int count,const string& filename){
    ofstream file(filename);
    for(int i=0;i<count;i++){
        file<<employees[i].id<<","
            <<employees[i].name<<","
            <<employees[i].department<<","
            <<employees[i].salary<<endl;
    }
    file.close();
    logAction("Saved all employee data.");
}
void addEmployee(Employee employees[],int& count){
    if(count>=MAX_EMPLOYEES){
        cout<<"Maximum employee limit reached."<<endl;
        return;
    }
    Employee emp;
    cout<<"Enter Employee ID: ";
    cin>>emp.id;
    cout<<"Enter Name: ";
    cin.ignore();
    getline(cin,emp.name);
    cout<<"Enter Department: ";
    getline(cin,emp.department);
    cout<<"Enter Salary: ";
    cin>>emp.salary;
    employees[count++]=emp;
    logAction("Added Employee ID: "+to_string(emp.id));
    cout<<"Employee added successfully."<<endl;
}
void viewEmployees(const Employee employees[],int count){
    cout<<endl<<"--- Employee List ---"<<endl;
    cout<<left<<setw(10)<<"ID"
        <<setw(20)<<"Name"
        <<setw(20)<<"Department"
        <<setw(10)<<"Salary"<<endl;
    for(int i=0;i<count;i++){
        cout<<left<<setw(10)<<employees[i].id
            <<setw(20)<<employees[i].name
            <<setw(20)<<employees[i].department
            <<setw(10)<<employees[i].salary<<endl;
    }}
void updateSalary(Employee employees[],int count,int id){
    for(int i=0;i<count;i++){
        if(employees[i].id==id){
            cout<<"Current Salary: "<<employees[i].salary<<endl;
            cout<<"Enter New Salary: ";
            cin>>employees[i].salary;
            logAction("Updated salary for Employee ID: "+to_string(id));
            cout<<"Salary updated."<<endl;
            return;
        }
    }
    cout<<"Employee not found."<<endl;
}
void calculateSalaryStats(const Employee employees[],int count){
    if(count==0){
        cout<<"No employee data available."<<endl;
        return;
    }
    double total=0;
    for(int i=0;i<count;i++){
        total+=employees[i].salary;
    }
    double average=total/count;
    cout<<"Total Salary: "<<total<<endl;
    cout<<"Average Salary: "<<average<<endl;
}
void logAction(const string& message){
    ofstream log("log.txt",ios::app);
    log<<message<<endl;
    log.close();
}