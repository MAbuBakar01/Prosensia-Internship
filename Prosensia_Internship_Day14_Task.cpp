#include<iostream>
#include<string>
using namespace std;
class Student{
	private:
	int rollNo;
	string name;
	int sub1,sub2, sub3;
	double average;
	int total;
 public:
   Student(int rNo, string n, int s1, int s2, int s3){
   	rollNo =rNo;
	 name =n;
	sub1 = s1;
	sub2 = s2;
	sub3 = s3;
   }
   void displayResult(){
   	total = sub1+ sub2+ sub3;
   	average = total/3;
   	cout<<"==============Result==========="<<endl;
   	cout<<"Student Name: "<<name<<endl;
   	cout<<"Roll Number: "<<rollNo<<endl;
   	cout<<"-------Obtained Marks (Total Marks = 100*3)--------"<<endl;
   	cout<<"1. Mathematics - "<<sub1<<endl;
   	cout<<"2. Physics - "<<sub2<<endl;
   	cout<<"3. Chemistry - "<<sub3<<endl;
   	cout<<"-------------------------------------------------"<<endl;
   	cout<<"Average Marks : "<<average<<endl;
   	cout<<"Total Obtained Marks : "<<total<<endl;
   	cout<<"================================="<<endl;
   }	
};
int main(){
	Student s1(122684, "Muhammad Abu Bakar", 78,91,72);
	s1.displayResult();
	return 0;
}
