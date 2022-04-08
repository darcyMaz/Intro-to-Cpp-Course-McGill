#include<iostream>
using namespace std;

class Base
{
    public:
        ~Base() {cout << "Base's des" << endl;}
};

class Derived: public Base
{
    public:
        ~Derived() {cout << "Derived's des" << endl;}
};

int main()
{
    Base* d = new Derived;
    delete d;
    return 0;
}