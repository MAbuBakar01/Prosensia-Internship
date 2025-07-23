#include <iostream>
#include <cmath>
using namespace std;

class Complex {
 private:
    float real, imag;
  public:
     Complex(float r = 0, float i = 0) {
        real = r;
        imag = i;
       }
    // Overloaded  operators (+, -, *)
    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, imag + c.imag);
      }
    Complex operator-(const Complex& c) const {
        return Complex(real - c.real, imag - c.imag);
        }
    Complex operator*(const Complex& c) const {
        return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
      }
    bool operator==(const Complex& c) const {
        return (real == c.real && imag == c.imag);
       }
    bool operator>(const Complex& c) const {
        return magnitude() > c.magnitude();
        }
     void display() const {
        cout<<real<<(imag >= 0 ? " + " : " - ")<<abs(imag)<< "i" << endl;
        }
    friend ostream& operator<<(ostream& out, const Complex& c);
    friend istream& operator>>(istream& in, Complex& c);

private:
    float magnitude() const {
        return sqrt(real * real + imag * imag);
    }
};
ostream& operator<<(ostream& out, const Complex& c) {
    out<<c.real<<(c.imag >= 0 ? " + " : " - ") <<abs(c.imag) << "i";
    return out;
}
istream& operator>>(istream& in, Complex& c) {
    cout<<"Enter real part: ";
    in>>c.real;
    cout<< "Enter imaginary part: ";
    in>>c.imag;
    return in;
}
int main() {
    Complex c1, c2;
    cout<<"Input for first complex number:\n";
    cin >> c1;
    cout<<"\nInput for second complex number:\n";
    cin>>c2;
    Complex sum=c1 + c2;
    Complex diff=c1 - c2;
    Complex product= c1 * c2;
    cout<<"\nResults:\n";
    cout<<"c1 = "<<c1<<endl;
    cout<<"c2 = "<<c2<<endl;
    cout<<"Sum = "<<sum<<endl;
    cout<<"Difference = " <<diff<<endl;
    cout<<"Product = " <<product<<endl;
    cout<<"\nEquality Check: "<<(c1==c2 ? "Equal" : "Not Equal")<<endl;
    cout<<"Magnitude Comparison: "<<(c1 > c2 ? "c1 > c2" : "c2 >= c1")<<endl;
    return 0;
}
