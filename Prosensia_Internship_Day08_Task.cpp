#include <iostream>
using namespace std;

bool isOdd(int n) {
    return n%2!= 0;
}
void conditionalSwap(int* x, int* y) {
    int diff = *x - *y;
    if (diff < 0) diff = -diff;
    if (diff > 10) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }}
void printArrayViaPointer(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " @ " << &arr[i] << endl;
    }
}
int* findFirstEven(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            return &arr[i];
        }
    }
    return nullptr; }
void incrementOddsByAddress(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (isOdd(arr[i])) {
            arr[i]++;
        }    }}
int main() {
    int a, b;
    int arr[5];
    cout << "Enter two integers (a and b): ";
    cin >> a >> b;
    cout << "Enter 5 array elements: ";
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }
    cout << "\n=== Pointer Logic Execution ===" << endl;
    cout << "Before Swap: a = " << a << ", b = " << b << endl;
    conditionalSwap(&a, &b);
    cout << "After Swap: a = " << a << ", b = " << b << endl;  
    cout << "Array Elements (value @ address):" << endl;
    printArrayViaPointer(arr, 5);
  int* evenPtr = findFirstEven(arr, 5);
    if (evenPtr) {
        cout << "First even found: " << *evenPtr << endl;
    } else {
        cout << "First even found: nullptr" << endl;
    }
       incrementOddsByAddress(arr, 5);
    cout << "Modified Array (Odds Incremented): ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
   return 0;
}