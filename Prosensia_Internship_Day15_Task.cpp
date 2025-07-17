#include<iostream>
#include<string>
using namespace std;
class Employee{
	protected:
	string name;
	int id;
	double salary;
	public:
		Employee(string n, int id, double slry){
		 name= n;
	       this ->id =id;
	       salary = slry;	
		}
		void showEmplyee(){
			cout<<"Employee Name: "<<name<<endl;
			cout<<"Employee ID: "<<id<<endl;
			cout<<"Salary: "<<salary<<endl;
		}
		
};
class Manager: public Employee{
	protected:
		double Bonus;
		public:
			Manager(string n, int id, double slry, double bon): Employee(n, id, slry){
			Bonus=bon;
			}
			void showManager(){
				cout<<"========================"<<endl;
				Employee::showEmplyee();
				cout<<"Designation: Manager"<<endl;
				cout<<"Bonus is "<<Bonus<<" PKR"<<endl;
				cout<<"========================"<<endl;
			}
};
class developer : public Employee{
	protected:
		string programLang;
		
		public:
				developer(string n, int id, double slry,string pl): Employee(n, id, slry){
			programLang=pl;
			}
			void showDeveloper(){
				cout<<"========================"<<endl;
				Employee::showEmplyee();
				cout<<"Designation: Developer"<<endl;
				cout<<"Programming Language: "<<programLang<<endl;
				cout<<"========================"<<endl;
			}
};
int main(){
	Manager m1("Asad Khan", 342533, 250000, 50000);
	developer d1("Saim Khan", 435498, 150000, "Python");
	m1.showManager();
	d1.showDeveloper();
	return 0;
	
}