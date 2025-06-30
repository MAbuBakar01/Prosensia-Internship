// ProsenSia Internship Muhammad Abu Bakar
#include<iostream>
using namespace std;
int factorial( int num );
void max(int a, int b, int c);
//====================Main Function========================
int main(){
	
cout<<	factorial(5)<<endl;
max(13, 5, 87);
	return 0 ;
}
//==================functions definition===========================
int factorial( int num ){
	 int fact=1;
	for(int i=1; i<=num; ++i){
		fact *=i;
	}
	cout<<"Factorial of "<<num<<" is ";
	return fact;
}

void max(int a, int b, int c){
	if(a>b){
		if(a>c){
			cout<<a<<" is greatest among "<<a<<" "<<b<<" and "<<c<<endl;
		}
	}
	if(b>a){
		if(b>c){
		cout<<b<<" is greatest among "<<a<<" "<<b<<" and "<<c<<endl;
		}
	}
	else{
		cout<<c<<" is greatest among "<<a<<" "<<b<<" and "<<c<<endl;
	}
}