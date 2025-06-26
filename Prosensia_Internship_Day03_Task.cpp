// Muhammad Abu Bakar Prosensia Internship Day#03
#include<iostream>
using namespace std;
int main(){
	string name;
	int age;
	float cgpa;
	cout<<"Enter Name: ";
	cin.ignore();
	getline(cin , name);
	cout<<"\nEnter Your Age: ";
	cin>>age;
	cout<<"\nEnter Your CGPA: ";
	cin>>cgpa;
	if (age>= 18 ){
		if(cgpa>=2.5){
		cout<<"You are Eligible to Apply for Internship at ProsenSia"<<endl;
			
		}
		else{
			cout<<"You are not eligible to Apply for Internship at ProsenSia, because your CGPPA is less than 2.5"<<endl;
		}
	}
	else{
		cout<<"You are not eligible to Apply for Internship at ProsenSia, because your age is less than 18"<<endl;
	}
	
	
	return 0;
}