// Muhammad Abu Bakar - ProsenSia Internship
#include<iostream>
using namespace std;

int main() {
    int number;
    bool isPrime=true;
    cout<<"Enter a Number: ";
    cin>> number;
    if (number<= 1) {
        isPrime = false;
    } else {
        for (int i = 2; i <= number/2; ++i) {
            if (number % i == 0) {
                isPrime = false;
                break; 
				  }
        } }

    if (isPrime)
        cout<<"Number is Prime" << endl;
     else
       cout<<"Number is not Prime" << endl;

    return 0;
}
