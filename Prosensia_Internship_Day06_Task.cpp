#include<iostream>
using namespace std;

int main() {
    int Array[5];
    int sum= 0;
    int greatest, smallest, even , odd;
    int index= 0; // for greatest
    int Mindex= 0;    // for smallest
    double average;

    // Storing numbers in Array
    cout<<"Enter 5 Numbers: ";
    for(int i=0; i<5; i++) {
        cin>>Array[i];
    }
    smallest= Array[0];
	greatest= Array[0];
    // Sum of All numbers
    //Maximum and Miimum number stored in Array With Index
    for(int j=0; j<5; j++)
	      {
        sum+= Array[j];
       
        if(Array[j]>greatest)
		 {
            greatest=Array[j];
            index=j;
        }

         if(Array[j]<smallest) {
            smallest=Array[j];
            Mindex=j;
        }
        if(Array[j]%2==0){
        	even=Array[j];
		}
		 if(Array[j]%2!=0){
        	odd=Array[j];
		}
    }
    average = sum/5;
      cout<<"Smallest Number is " <<smallest<<" stored in index "<<Mindex<<endl;
     cout<<"Greatest Number is " <<greatest<<" stored in index "<<index<<endl;
       cout<<"Sum of All Numbers stored in Array is "<<sum<<endl;
        cout<<"Average of All Numbers stored in Array is "<<average<<endl;
          cout<<"Even Number is " <<even<<endl;
           cout<<"Odd Number is " <<odd<<endl;
    return 0;
}
