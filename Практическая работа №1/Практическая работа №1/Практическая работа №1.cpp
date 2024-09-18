#include <iostream>
using namespace std;

int main()
{
    int Inumber;
    union {
        float Fnumber;
        int FnumberInInteger;
    };
    double Dnumber;
    unsigned int mask = 1;
    mask <<= 31;
    setlocale(0, "");
    cout << "int: " << sizeof(int) << " bytes\n";
    cout << "short int: " << sizeof(short int) << " bytes\n";
    cout << "long int: " << sizeof(long int) << " bytes\n";
    cout << "float: " << sizeof(float) << " bytes\n";
    cout << "double: " << sizeof(double) << " bytes\n";
    cout << "long double: " << sizeof(long double) << " bytes\n";
    cout << "char : " << sizeof(char) << " bytes\n";
    cout << "bool: " << sizeof(bool) << " bytes\n";
    
    cout << "Введите типа int: ";
    cin >> Inumber;
    cout << endl;

    for (int i = 1; i < 33; ++i) {
        if (mask & Inumber) {
            cout << '1';
        }
        else {
            cout << '0';
        }
        if (i == 1 || i % 8 == 0) {
            cout << ' ';
        }
        mask >>= 1;
    }
    cout << endl;
    cout << "Введите типа float: ";
    cin >> Fnumber;
    cout << endl;
    mask = 1;
    mask <<= 31;
    for (int i = 1; i < 33; ++i) {
        if (mask & FnumberInInteger) {
            cout << '1';
        }
        else {
            cout << '0';
        }
        if (i == 1 || i % 8 == 0) {
            cout << ' ';
        }
        mask >>= 1;
    }
    return 0;
}