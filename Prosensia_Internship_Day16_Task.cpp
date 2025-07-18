#include<iostream>
using namespace std;

class Shape {
public:
    virtual void draw() {
        cout<<"Drawing a generic shape..."<<endl;
    }
    virtual ~Shape() {}
};
class Circle : public Shape {
public:
    void draw() override{
        cout<< "Drawing a Circle "<<endl;
    }
};
class Rectangle : public Shape {
public:
    void draw() override {
        cout<<"Drawing a Rectangle "<<endl;
    }
};
class Triangle : public Shape {
public:
    void draw() override {
        cout<<"Drawing a Triangle"<<endl;
    }
};
int main() {
    const int size = 3;
    Shape* shapes[size];
    shapes[0] = new Circle();
    shapes[1] = new Rectangle();
    shapes[2] = new Triangle();
    cout << "Shape Drawing Simulator:\n" << endl;
    for (int i = 0; i < size; ++i) {
        shapes[i]->draw();  
    }
    for (int i = 0; i < size; ++i) {
        delete shapes[i];
    }
    return 0;
}
