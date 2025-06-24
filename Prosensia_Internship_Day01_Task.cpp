//Muhammad Abu Bakar
#include<iostream>
using namespace std;
int main(){
	string name;
	int age;
	float cgpa;
	cout<<"========== Welcome =========="<<endl;
	cout<<"Please Enter Your Name: ";
	getline(cin, name);
	cout<<"Please Enter Your Age: ";
	cin.ignore();
	cin>>age;
	cout<<"Please Enter Your CGPA: ";
	cin>>cgpa;
	cout<<"\n******* "<<name<<"'s Details *******"<<endl;
	cout<<"Your Name is "<<name<<endl;
	cout<<"Your Age is "<<age<<" years<<"endl;
	cout<<"Your CGPA is "<<cgpa<<endl;
	cout<<"*****************************************"<<endl;
	return 0;
}