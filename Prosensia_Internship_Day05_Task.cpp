// ProsenSia Internship Muhammad Abu Bakar
#include<iostream>
using namespace std;
int factorial( int num );
int max(int a, int b, int c);
//====================Main Function========================
int main(){
	int f,a,b,c;
cout<<"Enter a number: ";
cin>>f;
cout<<"\nEnter three Numbers: ";
cin>>a>>b>>c;	
cout<<	factorial(5)<<endl;
cout<<"Max Function result is: "<<max(a,b,c);
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
//=======Max Function==============
int max(int a, int b, int c){
	if(a>b){
		if(a>c){
		
			return a;
		}
	}
	if(b>a){
		if(b>c){
			return b;
		
		}
	}
	if(a==b==c){
		return 0;
	}
	if(a==b ){
	
	return a+b;
}
  if(a==c){
	return a+c;
}
 if(b==c){
	return b+c;
}
	else{
		return c;
		
	}
}