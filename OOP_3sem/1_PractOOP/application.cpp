#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "array.h"
#include "application.h"

ConsoleApp::ConsoleApp() {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    startY = 0;
    countRows = 7;
    menu = new std::string[countRows];
    menu[0] = "Задать массив";
    menu[1] = "Рассчитать среднее и СКО элементов массива";
    menu[2] = "Отсортировать массив";
    menu[3] = "Изменить размерность массива";
    menu[4] = "Изменить значение элемента массива";
    menu[5] = "Ввод в консоль элементов текущего объекта массива";
    menu[6] = "Выйти из приложения";
}

ConsoleApp::~ConsoleApp() {
    delete[] menu;
}

void ConsoleApp::startApp(Array& arr){
    int end = 1;
    while (end != -1){
        end = choiseMenu(arr);
    };
}

int ConsoleApp::choiseMenu(Array& arr) {
    system("cls"); 
    int choise = 0;
    int press = 0;
    int x = 0, y = startY;
    destCoord.Y = y;
    destCoord.X = x;
    
    for (int i = 0; i < countRows; ++i, ++y) {
        destCoord.Y = y;
        SetConsoleCursorPosition(hStdout, destCoord);
        std::cout << menu[i];
        std::cout.flush();
    }
    
    y = startY;
    destCoord.Y = y;
    SetConsoleCursorPosition(hStdout, destCoord);
    SetConsoleTextAttribute(hStdout, 240);
    std::cout << "> " << menu[choise];
    SetConsoleTextAttribute(hStdout, 07 | FOREGROUND_INTENSITY);
    std::cout.flush();
    
    while (_getch() != 0x0D) {
        press = _getch();
        system("color 0F");
        switch (press) {
        case 0x48:
            destCoord.Y = y;
            SetConsoleCursorPosition(hStdout, destCoord);
            std::cout << menu[choise] << "   ";
            std::cout.flush();
            if (choise == 0) {
                choise = countRows - 1;
                y = startY + countRows - 1;
            }
            else {
                choise--;
                y--;
            }
            destCoord.Y = y;
            SetConsoleCursorPosition(hStdout, destCoord);
            SetConsoleTextAttribute(hStdout, 240);
            std::cout << "> " << menu[choise];
            SetConsoleTextAttribute(hStdout, 07 | FOREGROUND_INTENSITY);
            std::cout.flush();
            break;
        case 0x50:
            destCoord.X = x;
            destCoord.Y = y;
            SetConsoleCursorPosition(hStdout, destCoord);
            std::cout << menu[choise] << "   ";
            std::cout.flush();
            if (choise == countRows - 1) {
                choise = 0;
                y = startY;
            }
            else {
                choise++;
                y++;
            }
            destCoord.X = x;
            destCoord.Y = y;
            SetConsoleCursorPosition(hStdout, destCoord);
            SetConsoleTextAttribute(hStdout, 240);
            std::cout << "> " << menu[choise];
            SetConsoleTextAttribute(hStdout, 07 | FOREGROUND_INTENSITY);
            std::cout.flush();
            break;
        }
    }
    
    SetConsoleTextAttribute(hStdout, 07);
    system("cls");
    
    switch (choise)
    {
    case 0:
        createArr(arr);
        break;
    case 1:
        calcAverenge(arr);
        break;
    case 2:
        SortArr(arr);
        break;
    case 3:
        changeSize(arr);
        break;
    case 4:
        changeElem(arr);
        break;
    case 5:
        printElem(arr);
        break;
    case 6:
        return -1;
    }
    
    return choise;
}

void ConsoleApp::createArr(Array& arr){
    int size;
    std::cout << "Введите размер массива\n";
    std::cin >> size;
    arr.changeSize(size);
    std::cout << "Введите значения массива\n";
    for(int i = 0; i < size; ++i){
        std::cout << "Элемент " << i << ": ";
        arr.cinNumber(i);
    }
    startY = 4;
}

void ConsoleApp::calcAverenge(Array& arr){
    std::cout << "Среднее: " << arr.calcAverenge() << std::endl;
    std::cout << "СКО: " << arr.calcStandardDeviation() << std::endl;
    std::cout << "Нажмите любую клавишу для продолжения...";
    _getch();
    startY = 4;
}

void ConsoleApp::SortArr(Array& arr){
    arr.sort(true);
    std::cout << "Отсортированный массив:\n";
    for(int i = 0; i < arr.getSize(); ++i){
        arr.coutNumber(i);
        std::cout << " ";
    }
    std::cout << "\nНажмите любую клавишу для продолжения...";
    _getch();
    startY = 4;
}

void ConsoleApp::changeSize(Array& arr){
    int size;
    std::cout << "Введите новый размер массива\n";
    std::cin >> size;
    arr.changeSize(size);
    if (size > 0) {
        std::cout << "Введите новые значения массива\n";
        for(int i = 0; i < size; ++i){
            std::cout << "Элемент " << i << ": ";
            arr.cinNumber(i);
        }
    }
    std::cout << "Нажмите любую клавишу для продолжения...";
    _getch();
    startY = 4;
}

void ConsoleApp::changeElem(Array& arr){
    int index;
    std::cout << "Введите номер элемента для изменения (0-" << arr.getSize()-1 << "): ";
    std::cin >> index;
    
    if (index >= 0 && index < arr.getSize()) {
        std::cout << "Текущее значение: ";
        arr.coutNumber(index);
        std::cout << "\nВведите новое значение: ";
        arr.cinNumber(index);
        std::cout << "Элемент изменен.\n";
    } else {
        std::cout << "Неверный индекс!\n";
    }
    
    std::cout << "Нажмите любую клавишу для продолжения...";
    _getch();
    startY = 4;
}

void ConsoleApp::printElem(Array& arr){
    int index;
    std::cout << "Введите номер элемента (0-" << arr.getSize()-1 << "): ";
    std::cin >> index;
    
    if (index >= 0 && index < arr.getSize()) {
        std::cout << "Элемент " << index << ": ";
        arr.coutNumber(index);
        std::cout << std::endl;
    } else {
        std::cout << "Неверный индекс!\n";
    }
    
    std::cout << "Нажмите любую клавишу для продолжения...";
    _getch();
    startY = 4;
}