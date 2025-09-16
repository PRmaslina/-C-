#include <iostream>
#include "application.h"
#include "array.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    ConsoleApp app;
    Array arr;
    app.startApp(arr);
    return 0;
}