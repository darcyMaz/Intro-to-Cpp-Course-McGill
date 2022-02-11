#include <iostream>
#include <string>
using namespace std;

int main()
{
    string a = "hello";
    a.append(",");
    string b = a.substr(0,a.size()-1);

    cout << b << endl;

    return 0;
}