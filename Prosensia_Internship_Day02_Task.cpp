//Muhammad Abu Bakar Prosensia Internship Day #02
#include<iostream>
using namespace std;
int main(){
	int sub1,sub2,sub3;  //sub -> Subject
	int sum;
	double average;
	cout<<"Enter Your Marks for Maths (1-100): ";
	cin>>sub1;
		cout<<"\nEnter Your Marks for Physics (1-100): ";
	cin>>sub2;
		cout<<"\nEnter Your Marks for Chemistry (1-100): ";
	cin>>sub3;
	sum=sub1+sub2+sub3;
	average=sum/3;
	cout<<"\nYour total Marks are "<<sum<<endl;
	cout<<"Average is "<<average<<endl;
	cout<<"------Subject wise Grades-------"<<endl;
	if (sub1>=80 && sub1<=100){
		cout<<"A Grade in Maths."<<endl;
	}
	else if (sub1>=65 && sub1<80) {
	     cout<<"B Grade in Maths."<<endl;	
	}
		else if (sub1>=50 && sub1<65) {
	     cout<<"C Grade in Maths."<<endl;	
	}
	else if(sub1<50){
		cout<<"You have been Failed in Maths."<<endl;
	}
	if (sub2>=80 && sub2<=100){
		cout<<"A Grade in Physics."<<endl;
	}
	else if (sub2>=65 && sub2<80) {
	     cout<<"B Grade in Physics."<<endl;	
	}
		else if (sub2>=50 && sub2<65) {
	     cout<<"C Grade in Physics."<<endl;	
	}
	else if(sub2<50){
		cout<<"You have been Failed in Physics."<<endl;
	}
	if (sub3>=80 && sub3<=100){
		cout<<"A Grade in Chemistry."<<endl;
	}
	else if (sub3>=65 && sub3<80) {
	     cout<<"B Grade in Chemistry."<<endl;	
	}
		else if (sub3>=50 && sub3<65) {
	     cout<<"C Grade in Chemistry."<<endl;	
	}
	else if(sub3<50){
		cout<<"You have been Failed in Chemistry."<<endl;
	}
	
	return 0;
	
}