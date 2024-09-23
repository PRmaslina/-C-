#include <iostream>
#include <windows.h>
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void cellInt(int intNumber) {
    unsigned int mask = 1;
    mask <<= 31;
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
        mask& intNumber ? putchar('1') : putchar('0');
        if (i == 1 || i % 8 == 0) {
            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
            putchar(' ');
        }
    }
    cout << "\n\n";
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void cellFloat(int floatCellInInt) {

    unsigned int mask = 1;
    mask <<= sizeof(float)*8 - 1;
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int i = 1; i < sizeof(float) * 8 + 1; ++i, mask >>= 1) {
        mask& floatCellInInt ? putchar('1') : putchar('0');
        if (i == 1){
            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
            putchar(' ');
        }
        else if (i == (sizeof(float) / 4 * 8 + 1)) {
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
            putchar(' ');
        }
        else if (i > (sizeof(float) / 4 * 8 + 1) && i % 8 == 0) {
            putchar(' ');
        }
    }
    cout << "\n\n";
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void cellDoub(int doubCellInArrInt[]) {

    unsigned int mask, elCount = 0;
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    for (int j = 0; j < sizeof(double) / sizeof(int); ++j) {
        mask = 1;
        mask <<= 31;
        for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
            mask& doubCellInArrInt[sizeof(double) / sizeof(int) - 1 - j] ? putchar('1') : putchar('0');
            elCount++;
            if (elCount == (sizeof(double) / 8) * 12) {
                SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
                putchar(' ');
            }
            else if (elCount == 1) {
                SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                putchar(' ');
            }
        }
    }
    cout << "\n\n";
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

}

int main()
{
    int intNumber, bitID, bitValue;
    unsigned int maskBitID[2] = {0,0};
    char input;
    union {
        float floatNumber;
        int floatCellInInt;
    };
    union {
        double doubNumber;
        int doubCellInArrInt[sizeof(double) / sizeof(int)];
    };
    setlocale(0, "");

    cout << "int: " << sizeof(int) << " bytes\n";
    cout << "short int: " << sizeof(short int) << " bytes\n";
    cout << "long int: " << sizeof(long int) << " bytes\n";
    cout << "float: " << sizeof(float) << " bytes\n";
    cout << "double: " << sizeof(double) << " bytes\n";
    cout << "long double: " << sizeof(long double) << " bytes\n";
    cout << "char : " << sizeof(char) << " bytes\n";
    cout << "bool: " << sizeof(bool) << " bytes\n";

    cout << "\nВведите переменную типа int: ";
    cin >> intNumber;
    cout << '\n';
    cellInt(intNumber);
    do{
        cout << "Нужно ли изменить какой-нибудь бит? (y/n): ";
        cin >> input;
        if (input != 'n'){
            cout << "\nвведите номер бита, считая справа налево: ";
            cin >> bitID;
            cout << "\nвведите значение бита: ";
            cin >> bitValue;
            maskBitID[1] = 1;
            maskBitID[1] <<= bitID-1;
            if (bitValue == 1) {
                if ((intNumber ^ maskBitID[1]) > intNumber) {
                    intNumber ^= maskBitID[1];
                }
            }
            else {
                if ((intNumber ^ maskBitID[1]) < intNumber) {
                    intNumber ^= maskBitID[1];
                }
            }
            cout << '\n';
            cellInt(intNumber);
            cout << "Получившееся число: " << intNumber << "\n\n";
        }
    } while (input != 'n');

    cout << "\nВведите переменную типа float: ";
    cin >> floatNumber;
    cout << '\n';
    cellFloat(floatCellInInt);
    do{
        cout << "Нужно ли изменить какой-нибудь бит? (y/n): ";
        cin >> input;
        if (input != 'n') {
            cout << "\nвведите номер бита, считая справа налево: ";
            cin >> bitID;
            cout << "\nвведите значение бита: ";
            cin >> bitValue;
            maskBitID[1] = 1;
            maskBitID[1] <<= bitID - 1;
            if (bitValue == 1) {
                if ((floatCellInInt ^ maskBitID[1]) > floatCellInInt) {
                    floatCellInInt ^= maskBitID[1];
                }
            }
            else {
                if ((floatCellInInt ^ maskBitID[1]) < floatCellInInt) {
                    floatCellInInt ^= maskBitID[1];
                }
            }
            cout << '\n';
            cellFloat(floatCellInInt);
            cout << "Получившееся число: " << floatNumber << "\n\n";
        }
    } while (input != 'n');

    cout << "\nВведите переменную типа double: ";
    cin >> doubNumber;
    cout << '\n';
    cellDoub(doubCellInArrInt);
    do {
        cout << "Нужно ли изменить какой-нибудь бит? (y/n): ";
        cin >> input;
        if (input != 'n') {
            cout << "\nвведите номер бита, считая справа налево: ";
            cin >> bitID;
            cout << "\nвведите значение бита: ";
            cin >> bitValue;
            if (bitID < 32) {
                maskBitID[0] = 0;
                maskBitID[1] = 1;
                maskBitID[1] <<= bitID - 1;
            }
            else {
                maskBitID[0] = 1;
                maskBitID[1] = 0;
                maskBitID[0] <<= bitID - 32 - 1;
            }
            if (bitValue == 1) {
                if (((doubCellInArrInt[1] ^ maskBitID[0]) + (doubCellInArrInt[0] ^ maskBitID[1])) > doubCellInArrInt[0]+ doubCellInArrInt[1]) {
                    doubCellInArrInt[1] ^= maskBitID[0];
                    doubCellInArrInt[0] ^= maskBitID[1];
                }
            }
            else {
                if (((doubCellInArrInt[1] ^ maskBitID[0]) + (doubCellInArrInt[0] ^ maskBitID[1])) < doubCellInArrInt[0] + doubCellInArrInt[1]) {
                    doubCellInArrInt[1] ^= maskBitID[0];
                    doubCellInArrInt[0] ^= maskBitID[1];
                }
            }
            cout << '\n';
            cellDoub(doubCellInArrInt);
            cout << "\nПолучившееся число: " << doubNumber << "\n\n";
        }
    } while (input != 'n');

    return 0;
}