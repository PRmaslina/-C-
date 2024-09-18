#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int Inumber, elCount = 0;
    union {
        float Fnumber;
        int FcellInInt;
    };
    union {
        double Dnumber;
        int DcellInArrInt[sizeof(double) / sizeof(int)];
    };
    unsigned int mask;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    setlocale(0, "");

    cout << "int: " << sizeof(int) << " bytes" << endl;
    cout << "short int: " << sizeof(short int) << " bytes" << endl;
    cout << "long int: " << sizeof(long int) << " bytes" << endl;
    cout << "float: " << sizeof(float) << " bytes" << endl;
    cout << "double: " << sizeof(double) << " bytes" << endl;
    cout << "long double: " << sizeof(long double) << " bytes" << endl;
    cout << "char : " << sizeof(char) << " bytes" << endl;
    cout << "bool: " << sizeof(bool) << " bytes" << endl;
    cout << endl;

    cout << "Введите переменную типа int: ";
    cin >> Inumber;
    cout << endl;
    mask = 1;
    mask <<= 31;

    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
        mask & Inumber ? putchar('1') : putchar('0');
        if (i == 1 || i % 8 == 0) {
            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
            putchar(' ');
        }
    }
    cout << endl << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << "Введите переменную типа float: ";
    cin >> Fnumber;
    cout << endl;
    mask = 1;
    mask <<= 31;

    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int i = 1; i < sizeof(float) * 8 + 1; ++i, mask >>= 1) {
        mask & FcellInInt ? putchar('1') : putchar('0');
        if (i < (sizeof(float) / 4 * 8 + 1)) {
            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
        }
        if (i == (sizeof(float) / 4 * 8 + 1)) {
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
            putchar(' ');
        }
        if (i == 1 || ( i > (sizeof(float) / 4 * 8 + 1) && i % 8 == 0 )) {
            putchar(' ');
        }
    }
    cout << endl << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << "Введите переменную типа double: ";
    cin >> Dnumber;
    cout << endl;

    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int j = 0; j < sizeof(double) / sizeof(int); ++j) {
        mask = 1;
        mask <<= 31;
        for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
            mask & DcellInArrInt[sizeof(double) / sizeof(int) - 1 - j] ? putchar('1') : putchar('0');
            elCount++;
            if (elCount == (sizeof(double) / 8) * 12) {
                SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
                putchar(' ');
            }
            if (elCount == 1) {
                SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                putchar(' ');
            }
        }
    }
    cout << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    
    return 0;
}