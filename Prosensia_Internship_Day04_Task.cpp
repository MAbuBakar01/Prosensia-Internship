//Muhammad Abu Bakar ProsenSia Internship
#include<iostream>
using namespace std;
int main(){
	int number;
	int reversedNum=0;
	cout<<"Enter a Number: ";
	cin>>number;
	cout<<"\nOriginal Number is "<<number <<endl;
	while (number!=0){
		int digit= number%10;
	reversedNum = reversedNum * 10 + digit;
	number /= 10;
	}
	
	cout<<"Reversed Number is "<<reversedNum<<endl;
	return 0;
}