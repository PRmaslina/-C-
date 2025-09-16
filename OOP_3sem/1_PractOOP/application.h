#include <string>
#include <Windows.h>
#include "array.h"

class ConsoleApp
{
    HANDLE hStdout;
    COORD destCoord;
    int countRows;
    int startY;
    std::string* menu;

public:
    ConsoleApp();
    ~ConsoleApp();
    void startApp(Array& arr);
    int choiseMenu(Array& arr);
    void createArr(Array& arr);
    void calcAverenge(Array& arr);
    void SortArr(Array& arr);
    void changeSize(Array& arr);
    void changeElem(Array& arr);
    void printElem(Array& arr);
};
