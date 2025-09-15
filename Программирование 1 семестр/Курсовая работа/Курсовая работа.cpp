#include <iostream>
#include <chrono>
#include <fstream>
#include <windows.h>
#include <map>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <locale>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

void cellInt(int intNumber) {
    unsigned int mask = 1;
    mask <<= 31;
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
    for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
        mask& intNumber ? putchar('1') : putchar('0');
        if (i == 1 || i % 8 == 0) {
            SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
            putchar(' ');
        }
    }
    cout << "\n\n";
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void cellFloat(int floatCellInInt) {

    unsigned int mask = 1;
    mask <<= sizeof(float) * 8 - 1;
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
    for (int i = 1; i < sizeof(float) * 8 + 1; ++i, mask >>= 1) {
        mask& floatCellInInt ? putchar('1') : putchar('0');
        if (i == 1) {
            SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
            putchar(' ');
        }
        else if (i == (sizeof(float) / 4 * 8 + 1)) {
            SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE);
            putchar(' ');
        }
        else if (i > (sizeof(float) / 4 * 8 + 1) && i % 8 == 0) {
            putchar(' ');
        }
    }
    cout << "\n\n";
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void cellDoub(int doubCellInArrInt[]) {

    unsigned int mask, elCount = 0;
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
    for (int j = 0; j < sizeof(double) / sizeof(int); ++j) {
        mask = 1;
        mask <<= 31;
        for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
            mask& doubCellInArrInt[sizeof(double) / sizeof(int) - 1 - j] ? putchar('1') : putchar('0');
            elCount++;
            if (elCount == (sizeof(double) / 8) * 12) {
                SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE);
                putchar(' ');
            }
            else if (elCount == 1) {
                SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
                putchar(' ');
            }
        }
    }
    cout << "\n\n";
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

int firstpPractic(){
	system("cls");
    int intNumber, bitID, bitValue;
    unsigned int maskBitID[2] = { 0,0 };
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
    do {
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
    do {
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
                if (((doubCellInArrInt[1] ^ maskBitID[0]) + (doubCellInArrInt[0] ^ maskBitID[1])) > doubCellInArrInt[0] + doubCellInArrInt[1]) {
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

void equatingArr(int arr[], int sourceArr[], const int sizeArr) {
    for (int i = 0; i < sizeArr; i++) {
        arr[i] = sourceArr[i];
    }
}

void printArr(int arr[], const int sizeArr) {
    for (int i = 0; i < sizeArr; ++i) {
        cout << arr[i] << " ";
    }
}

void createArr(int arr[], const int sizeArr) {
    srand(time(0));
    int start = -99, end = 99;
    for (int i = 0; i < sizeArr; i++) {
        arr[i] = rand() % (end - start + 1) + start;
    }
}

void findMaxAndMinElArr(int arr[], int unsortArr[], const int sizeArr) {
    int max, min;
    auto timeStart1 = chrono::steady_clock::now();
    max = arr[sizeArr - 1];
    min = arr[0];
    auto timeEnd1 = chrono::steady_clock::now();
    cout << "Поиск в остортированном массиве time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n" << "max: " << max << "  min: " << min << endl;
    auto timeStart2 = chrono::steady_clock::now();
    max = unsortArr[0];
    min = unsortArr[0];
    for (int i = 1; i < sizeArr; ++i) {
        if (unsortArr[i] > max) {
            max = unsortArr[i];
        }
        if (unsortArr[i] < min) {
            min = unsortArr[i];
        }
    }
    auto timeEnd2 = chrono::steady_clock::now();
    cout << "Поиск в неостортированном массиве time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n" << "max: " << max << "  min: " << min << endl;
}

void findAverageValue(int arr[], int unsortArr[], const int sizeArr) {
    int max, min, average, count = 0, flag = 0;
    auto timeStart1 = chrono::steady_clock::now();
    max = arr[sizeArr - 1];
    min = arr[0];
    average = (max + min) / 2;
    for (int i = 0; i < sizeArr && arr[i] <= average; ++i) {
        if (arr[i] == average) {
            //cout << i << " ";
            ++count;
        }
    }
    auto timeEnd1 = chrono::steady_clock::now();
    flag = 0;
    for (int i = 0; i < sizeArr; ++i) {
        if (arr[i] == average) {
            cout << i << " ";
            flag = 1;
        }
        else if (flag == 1) {
            break;
        }
    }
    cout << " : индексы элементов равных среднему, всего их: " << count << endl;
    cout << "Поиск и вывод индексов в остортированном массиве time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n" << "среднее от max и min: " << average << endl;
    auto timeStart2 = chrono::steady_clock::now();
    count = 0;
    average = 0;
    max = -sizeArr;
    min = sizeArr;
    for (int i = 0; i < sizeArr; ++i) {
        if (unsortArr[i] > max) {
            max = unsortArr[i];
        }
        if (unsortArr[i] < min) {
            min = unsortArr[i];
        }
    }
    average = (max + min) / 2;
    for (int i = 0; i < sizeArr; ++i) {
        if (unsortArr[i] == average) {
            ++count;
        }
    }
    auto timeEnd2 = chrono::steady_clock::now();
    for (int i = 0; i < sizeArr; ++i) {
        if (unsortArr[i] == average) {
            cout << i << " ";
        }
    }
    cout << " : индексы элементов равных среднему, всего их: " << count << endl;
    cout << "Поиск и вывод индексов в неостортированном массиве time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n" << "среднее от max и min: " << average << endl;
}

void findLessThenNumb(int arr[], int number, const int sizeArr) {
    int count = 0;
    for (int i = 0; i < sizeArr; ++i) {
        if (arr[i] < number) {
            ++count;
        }
        else {
            break;
        }
    }
    cout << "\nКол-во элементов меньших чем введёное число: " << count;
}

void findMoreThenNumb(int arr[], int number, const int sizeArr) {
    int count = 0;
    for (int i = sizeArr - 1; i >= 0; --i) {
        if (arr[i] > number) {
            ++count;
        }
        else {
            break;
        }
    }
    cout << "\nКол-во элементов больших чем введёное число: " << count;
}

int binarySearch(int arr[], int number, int start, int end) {
    int rem = 0;
    if ((end - start) / 2 == 0) {
        rem = 1;
    }
    int middleNumb = arr[start + (end - start) / 2 + rem];
    if (middleNumb == number) {
        return start + (end - start) / 2 + rem;
    }
    else if (start + 1 == end || start == end + 1) {
        return -1;
    }
    if (middleNumb > number) {
        end = start + (end - start) / 2 + rem;
        binarySearch(arr, number, start, end);
    }
    else {
        start = start + (end - start) / 2 + rem;
        binarySearch(arr, number, start, end);
    }
}

int simpleSearch(int arr[], int number, const int sizeArr) {
    for (int i = 0; i < sizeArr; ++i) {
        if (arr[i] == number) {
            return i;
        }
    }
    return -1;
}

void tryFindEl(int arr[], int number, const int sizeArr) {
    int idEl;
    auto timeStart1 = chrono::steady_clock::now();
    idEl = binarySearch(arr, number, 0, sizeArr - 1);
    auto timeEnd1 = chrono::steady_clock::now();
    if (idEl == -1) {
        cout << "Такого элемента нет в массиве\n";
    }
    else {
        cout << "ID найденного элемента: " << idEl << endl;
    }
    cout << "Бинарный поиск  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";
    auto timeStart2 = chrono::steady_clock::now();
    idEl = simpleSearch(arr, number, sizeArr);
    auto timeEnd2 = chrono::steady_clock::now();
    if (idEl == -1) {
        cout << "Такого элемента нет в массиве\n";
    }
    else {
        cout << "ID найденного элемента: " << idEl << endl;
    }
    cout << "Обычный поиск  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
}

void swapElTime(int arr[], int firstElId, int secondElId) {
    auto timeStart = chrono::steady_clock::now();
    swap(arr[firstElId], arr[secondElId]);
    auto timeEnd = chrono::steady_clock::now();
    cout << "swap time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

template <const int sizeArr>
void bubbleSort(int arr[]) {
    bool isChanged = true;
    int end = sizeArr - 1;
    while (isChanged == true) {
        isChanged = false;
        for (int i = 0; i < end; ++i) {
            if (arr[i + 1] < arr[i]) {
                swap(arr[i + 1], arr[i]);
                isChanged = true;
            }
        }
        --end;
    }
}

template <const int sizeArr>
void shakerSort(int arr[]) {
    bool isChanged = true;
    int start = 0, end = sizeArr - 1;
    while (isChanged == true) {
        isChanged = false;
        for (int i = start; i < end; ++i) {
            if (arr[i + 1] < arr[i]) {
                swap(arr[i + 1], arr[i]);
                isChanged = true;
            }
        }
        --end;
        if (!isChanged) {
            break;
        }
        for (int i = end; i > start; --i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                isChanged = true;
            }
        }
        ++start;
    }
}

template <const int sizeArr>
void combSort(int arr[]) {
    float k = 1.247;
    bool isChanged = true;
    int end = sizeArr - 1, gap = sizeArr - 1;
    while (gap != 1) {
        for (int i = 0; i < sizeArr - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i + gap], arr[i]);
            }
        }
        gap /= k;
    }

    while (isChanged == true) {
        isChanged = false;
        for (int i = 0; i < end; ++i) {
            if (arr[i + 1] < arr[i]) {
                swap(arr[i + 1], arr[i]);
                isChanged = true;
            }
        }
        --end;
    }
}

template <const int sizeArr>
void insertSort(int arr[]) {
    int end = sizeArr - 1, stepCount;
    for (int start = 1; start <= end; ++start) {
        stepCount = 0;
        while (arr[start - stepCount] < arr[start - 1 - stepCount]) {
            swap(arr[start - stepCount], arr[start - 1 - stepCount]);
            ++stepCount;
        }
    }
}

void quickSortSep(int arr[], int start, int end) {
    int pivot = start;
    ++start;
    if (start >= end) {
        return;
    }
    for (int i = start; i <= end; ++i) {
        if (arr[i] < arr[pivot]) {
            swap(arr[start], arr[i]);
            ++start;
        }
    }
    swap(arr[pivot], arr[start - 1]);
    quickSortSep(arr, pivot, start - 1);
    quickSortSep(arr, start, end);
}

template <const int sizeArr>
void quickSortMain(int arr[]) {
    quickSortSep(arr, 0, sizeArr - 1);
}

void mergeSortStep(int arr[], const int sizeArr, int start, int end, int twoSortArr[]) {
    int parity = (end - start + 1) % 2;
    if (end - start <= 1) {
        if (end - start == 1 && arr[end] < arr[start]) {
            swap(arr[start], arr[end]);
        }
        return;
    }
    mergeSortStep(arr, sizeArr, start, (end + start) / 2 - parity, twoSortArr);
    mergeSortStep(arr, sizeArr, (end + start) / 2 + 1 - parity, end, twoSortArr);
    int ind = 0;
    int lArrIndex = start, rArrIndex = (end + start) / 2 + 1 - parity;
    for (int i = 0; i < (end - start + 1); ++i) {
        if (lArrIndex <= (end + start) / 2 - parity && rArrIndex <= end) {
            if (arr[lArrIndex] > arr[rArrIndex]) {
                twoSortArr[ind] = arr[rArrIndex];
                ++rArrIndex;
                ++ind;
            }
            else {
                twoSortArr[ind] = arr[lArrIndex];
                ++lArrIndex;
                ++ind;
            }
        }
        else if (rArrIndex > end) {
            twoSortArr[ind] = arr[lArrIndex];
            ++lArrIndex;
            ++ind;
        }
        else {
            twoSortArr[ind] = arr[rArrIndex];
            ++rArrIndex;
            ++ind;
        }
    }
    ind = 0;
    for (int i = start; i <= end; ++i) {
        arr[i] = twoSortArr[ind];
        ++ind;
    }
}

template <const int sizeArr>
void mergeSortMain(int arr[]) {
    int twoSortArr[sizeArr];
    mergeSortStep(arr, sizeArr, 0, sizeArr - 1, twoSortArr);
}

void leadTime(void (*func)(int[]), const char name[], int arr[]) {
    auto timeStart = chrono::steady_clock::now();
    func(arr);
    auto timeEnd = chrono::steady_clock::now();
    cout << "Время выполнения " << name << ":  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

template <const int sizeArr>
void choiseSort(int arr[], int unsortArr[]) {
    int choise;
    cin >> choise;
    switch (choise) {
    case 0:
        cout << "\n";
        leadTime(bubbleSort<sizeArr>, "bubbleSort", arr);
        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    case 1:
        cout << "\n";
        leadTime(shakerSort<sizeArr>, "shakerSort", arr);
        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    case 2:
        cout << "\n";
        leadTime(combSort<sizeArr>, "combSort", arr);
        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    case 3:
        cout << "\n";
        leadTime(insertSort<sizeArr>, "insertSort", arr);
        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    case 4:
        cout << "\n";
        leadTime(quickSortMain<sizeArr>, "quickSort", arr);
        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    case 5:
        cout << "\n";
        leadTime(mergeSortMain<sizeArr>, "mergeSort", arr);
        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    case 6:
        equatingArr(arr, unsortArr, sizeArr);
        cout << "\n";
        leadTime(bubbleSort<sizeArr>, "bubbleSort", arr);

        equatingArr(arr, unsortArr, sizeArr);
        cout << "\n";
        leadTime(shakerSort<sizeArr>, "shakerSort", arr);

        equatingArr(arr, unsortArr, sizeArr);
        cout << "\n";
        leadTime(combSort<sizeArr>, "combSort", arr);

        equatingArr(arr, unsortArr, sizeArr);
        cout << "\n";
        leadTime(insertSort<sizeArr>, "insertSort", arr);

        equatingArr(arr, unsortArr, sizeArr);
        cout << "\n";
        leadTime(quickSortMain<sizeArr>, "quickSort", arr);

        equatingArr(arr, unsortArr, sizeArr);
        cout << "\n";
        leadTime(mergeSortMain<sizeArr>, "mergeSort", arr);

        cout << "\nПолучившийся массив: ";
        printArr(arr, sizeArr);
        break;
    }
}

int secondPractic() {
	system("cls");
    setlocale(LC_CTYPE, "Russian");
    constexpr int sizeArr = 100;
    int choise, arr[sizeArr], unsortArr[sizeArr], inputNumber, firstElId, secondElId;
    bool isSorted = false;
    cout << "Исходный массив: ";
    createArr(unsortArr, sizeArr);
    printArr(unsortArr, sizeArr);
    equatingArr(arr, unsortArr, sizeArr);
    do { // Меню выбора
        if (isSorted) {
            cout << "\n\nВыберите нужный пункт:"
                << "\n 0) Переформировать массив"
                << "\n 1) Отсортировать массив"
                << "\n 2) Найти максимальный и минимальный элементы массива"
                << "\n 3) Вывести среднее значение max и min элементов и индексы элементов котрые ему равны"
                << "\n 4) Вывести кол-во элементов МЕНЬШЕ введённого числа"
                << "\n 5) Вывести кол-во элементов БОЛЬШЕ введённого числа"
                << "\n 6) Вывести информацию о том есть ли введённое число в массиве"
                << "\n 7) Поменять местами элементы массива"
                << "\n-1) Закончить выполнение программы\n";
            cin >> choise;
            switch (choise)
            {
            case(0): // Переформировать массвив  
                cout << "Новый исходный массив: ";
                isSorted = false;
                createArr(unsortArr, sizeArr);
                printArr(unsortArr, sizeArr);
                equatingArr(arr, unsortArr, sizeArr);
                break;
            case(1): // Отсортировать массив  
                cout << "\nВыберите выриант сортировки:"
                    << "\n 0) Bubble sort"
                    << "\n 1) Shaker sort"
                    << "\n 2) Comb sort"
                    << "\n 3) Insert sort"
                    << "\n 4) Quick sort"
                    << "\n 5) Merge sort"
                    << "\n 6) Все разом\n";
                equatingArr(arr, unsortArr, sizeArr);
                choiseSort<sizeArr>(arr, unsortArr);
                break;
            case(2): // Найти максимальный и минимальный элементы массива
                findMaxAndMinElArr(arr, unsortArr, sizeArr);
                break;
            case(3): // Вывести среднее значение max и min элементов и индексы элементов котрые ему равны
                findAverageValue(arr, unsortArr, sizeArr);
                break;
            case(4): // Вывести кол-во элементов МЕНЬШЕ введённого числа
                cout << "Введите число: ";
                cin >> inputNumber;
                findLessThenNumb(arr, inputNumber, sizeArr);
                break;
            case(5): // Вывести кол-во элементов БОЛЬШЕ введённого числа
                cout << "Введите число: ";
                cin >> inputNumber;
                findMoreThenNumb(arr, inputNumber, sizeArr);
                break;
            case(6): // Вывести информацию о том есть ли введённое число в массвиве
                cout << "Введите число: ";
                cin >> inputNumber;
                tryFindEl(arr, inputNumber, sizeArr);
                break;
            case(7): // Поменять местами элементы массива
                cout << "Введите через пробел номера двух элементов массива: ";
                cin >> firstElId >> secondElId;
                swapElTime(arr, firstElId, secondElId);
                cout << "Полученный массив: ";
                printArr(arr, sizeArr);
                isSorted = false;
                break;
            }
        }
        else {
            cout << "\n\nВыберите нужный пункт:"
                << "\n 0) Переформировать массив"
                << "\n 1) Отсортировать массив"
                << "\n 7) Поменять местами элементы массива"
                << "\n-1) Закончить выполнение программы\n";
            cin >> choise;
            switch (choise)
            {
            case(0): // Переформировать массвив  
                cout << "Новый исходный массив: ";
                isSorted = false;
                createArr(unsortArr, sizeArr);
                printArr(unsortArr, sizeArr);
                equatingArr(arr, unsortArr, sizeArr);
                break;
            case(1): // Отсортировать массив  
                cout << "\nВыберите выриант сортировки:"
                    << "\n 0) Bubble sort"
                    << "\n 1) Shaker sort"
                    << "\n 2) Comb sort"
                    << "\n 3) Insert sort"
                    << "\n 4) Quick sort"
                    << "\n 5) Merge sort"
                    << "\n 6) Все разом\n";
                isSorted = true;
                choiseSort<sizeArr>(arr, unsortArr);
                break;
            case(7): // Поменять местами элементы массива
                cout << "Введите через пробел номера двух элементов массива: ";
                cin >> firstElId >> secondElId;
                swapElTime(arr, firstElId, secondElId);
                cout << "Полученный массив: ";
                printArr(arr, sizeArr);
                isSorted = false;
                break;
            }
        }
    } while (choise != -1);
    return 0;
} // 2 практическая

void printNumber(int number, int x, int y) {
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << setw(5) << number << '\r';
	cout.flush();
}

void printEl(int number, char colour, int** pattern, int rows, int colums) {
	int el, x, y;
	switch (colour) {
	case 'r':
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case 'g':
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case 'b':
		SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case 'y':
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case 'v':
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case 'l':
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	}
	el = pattern[number] - pattern[0];
	x = (el % colums) * 5;
	y = (el + 1 == colums * rows ? rows - 1 : el / colums);
	printNumber(*pattern[number], x, y);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void printMat(int** mat, int rows, int colums, int x, int y) {
	int* turtle = &mat[0][0];
	for (int i = 1; i <= rows * colums; ++i, ++turtle, x += 5) {
		printNumber(*turtle, x, y);
		if (i % colums == 0) {
			++y;
			x -= 5 * colums;
		}
	}
}

void fillMatSpiral(int** mat, int rows, int colums, int speed) {
	system("cls");
	int* turtle = &mat[0][0];
	int k = 1, c = 1, x = 0, y = 0;
	int f = 1, l = 1;
	bool flag = true;
	char side = 'r';
	srand(time(0));
	while (c <= rows * colums) {
		switch (side) {
		case 'r':
			k = 1;
			side = 'd';
			break;
		case 'd':
			k = colums;
			side = 'l';
			break;
		case 'l':
			k = -1;
			side = 'u';
			break;
		case 'u':
			k = -colums;
			side = 'r';
			break;
		}
		if (side == 'd' || side == 'u') {
			for (int i = 0; colums - l == 0 ? i <= colums - l : i < colums - l; ++i, c++, side == 'd' ? x += 5 : x -= 5, turtle += k) {
				*turtle = rand() % (rows * colums) + 1;
				printNumber(*turtle, x, y);
				Sleep(speed);
			}
			flag ? flag = false : l += 1;
		}
		else {
			for (int i = 0; rows - f == 0 ? i <= rows - f : i < rows - f; ++i, c++, side == 'l' ? y += 1 : y -= 1, turtle += k) {
				*turtle = rand() % (rows * colums) + 1;
				printNumber(*turtle, x, y);
				Sleep(speed);
			}
			f += 1;
		}
	}
	destCoord.X = 0;
	destCoord.Y = rows + 1;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void fillMatVert(int** mat, int rows, int colums, int speed) {
	system("cls");
	int* turtle = &mat[0][0];
	int k = 1, c = 1, x = 0, y = 0;
	char side = 'd';
	srand(time(0));
	while (c <= rows * colums) {
		switch (side) {
		case 'd':
			k = colums;
			side = 'u';
			break;
		case 'u':
			k = -colums;
			side = 'd';
			break;
		}
		for (int i = 0; i < rows; ++i, ++c, turtle += k) {
			*turtle = rand() % (rows * colums) + 1;
			printNumber(*turtle, x, y);
			Sleep(speed);
			side == 'u' ? y += 1 : y -= 1;
		}
		turtle++;
		x += 5;
		side == 'u' ? y -= 1 : y += 1;
		turtle -= k;
	}
	destCoord.X = 0;
	destCoord.Y = rows + 1;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void fillMatSimple(int** mat, int rows, int colums, int speed) {
	system("cls");
	int* turtle = &mat[0][0];
	int c = 0, x = 0, y = 0;
	srand(time(0));
	for (int i = 0; i < rows * colums; ++i, turtle++, c++) {
		*turtle = rand() % (rows * colums) + 1;
		x = (c % colums) * 5;
		y = (c + 1 == colums * rows ? rows - 1 : c / colums);
		printNumber(*turtle, x, y);
		Sleep(speed);
	}
	destCoord.X = 0;
	destCoord.Y = rows + 1;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void replaceBlocksRound(int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	int* turtle2;
	int c = 0;
	int rowsParity, columsParity;
	rows % 2 == 0 ? rowsParity = 0 : rowsParity = 1;
	colums % 2 == 0 ? columsParity = 0 : columsParity = 1;
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (colums / 2 + columsParity);
		swap(*turtle, *turtle2);
		turtle2 += (rows / 2 + rowsParity) * rows;
		swap(*turtle, *turtle2);
		turtle2 = turtle + (rows / 2 + rowsParity) * rows;
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[0][0] + colums * (i / (colums / 2)) : turtle++;
	}
}

void replaceBlocksObliq(int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	int* turtle2;
	int rowsParity, columsParity;
	rows % 2 == 0 ? rowsParity = 0 : rowsParity = 1;
	colums % 2 == 0 ? columsParity = 0 : columsParity = 1;
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (colums / 2 + columsParity) + (rows / 2 + rowsParity) * rows;
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[0][0] + colums * (i / (colums / 2)) : turtle++;
	}
	turtle = &mat[rows / 2 + rowsParity][0];
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (colums / 2 + columsParity) - (rows / 2 + rowsParity) * rows;
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[rows / 2 + rowsParity][0] + colums * (i / (colums / 2)) : turtle++;
	}
}

void replaceBlocksVert(int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	int* turtle2;
	int rowsParity, columsParity;
	rows % 2 == 0 ? rowsParity = 0 : rowsParity = 1;
	colums % 2 == 0 ? columsParity = 0 : columsParity = 1;
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (rows / 2 + rowsParity) * rows;
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[0][0] + colums * (i / (colums / 2)) : turtle++;
	}
	turtle = &mat[0][colums / 2 + columsParity];
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (rows / 2 + rowsParity) * rows;
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[0][colums / 2 + columsParity] + colums * (i / (colums / 2)) : turtle++;
	}
}

void replaceBlocksHor(int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	int* turtle2;
	int rowsParity, columsParity;
	rows % 2 == 0 ? rowsParity = 0 : rowsParity = 1;
	colums % 2 == 0 ? columsParity = 0 : columsParity = 1;
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (colums / 2 + columsParity);
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[0][0] + colums * (i / (colums / 2)) : turtle++;
	}
	turtle = &mat[rows / 2 + rowsParity][0];
	for (int i = 1; i <= (colums / 2) * (rows / 2); ++i) {
		turtle2 = turtle + (colums / 2 + columsParity);
		swap(*turtle, *turtle2);
		i % (colums / 2) == 0 ? turtle = &mat[rows / 2 + rowsParity][0] + colums * (i / (colums / 2)) : turtle++;
	}
}

void arithOperMat(int** mat, int rows, int colums, char operation, int number) {
	int* turtle = &mat[0][0];
	for (int i = 0; i < rows * colums; ++i, ++turtle) {
		switch (operation) {
		case '+':
			*turtle += number;
			break;
		case '-':
			*turtle -= number;
			break;
		case '*':
			*turtle *= number;
			break;
		case '/':
			*turtle /= number;
			break;
		}
	}
}

void createSpiralPointersPattern(int** pattern, int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	int k = 1, c = 0;
	int f = 1, l = 1;
	bool flag = true;
	char side = 'r';
	while (c < rows * colums) {
		switch (side) {
		case 'r':
			k = 1;
			side = 'd';
			break;
		case 'd':
			k = colums;
			side = 'l';
			break;
		case 'l':
			k = -1;
			side = 'u';
			break;
		case 'u':
			k = -colums;
			side = 'r';
			break;
		}
		if (side == 'd' || side == 'u') {
			for (int i = 0; colums - l == 0 ? i <= colums - l : i < colums - l; ++i, c++, turtle += k) {
				pattern[c] = turtle;
			}
			flag ? flag = false : l += 1;
		}
		else {
			for (int i = 0; rows - f == 0 ? i <= rows - f : i < rows - f; ++i, c++, turtle += k) {
				pattern[c] = turtle;
			}
			f += 1;
		}
	}
}

void createVertPointersPattern(int** pattern, int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	int k, c = 1;
	char side = 'd';
	while (c < rows * colums) {
		switch (side) {
		case 'd':
			k = colums;
			side = 'u';
			break;
		case 'u':
			k = -colums;
			side = 'd';
			break;
		}
		for (int i = 0; i < rows; ++i, ++c, turtle += k) {
			pattern[c - 1] = turtle;
		}
		turtle++;
		turtle -= k;
	}
}

void createVertPointersSimple(int** pattern, int** mat, int rows, int colums) {
	int* turtle = &mat[0][0];
	for (int i = 0; i < rows * colums; ++i, turtle++) {
		pattern[i] = turtle;
	}
}

void bubbleSort(int** mat, int** pattern, int rows, int colums, int speed) {
	system("cls");
	printMat(mat, rows, colums, 0, 0);
	int x, y, el;
	bool isChanged = true;
	int** end = &pattern[rows * colums - 1];
	while (isChanged == true) {
		isChanged = false;
		for (int** i = pattern; i < end; ++i) {
			printEl(i - pattern, 'r', pattern, rows, colums);
			printEl((i - pattern) + 1, 'y', pattern, rows, colums);
			Sleep(speed / 2);
			if (**(i + 1) < **i) {
				swap(**(i + 1), **i);
				isChanged = true;

				printEl(i - pattern, 'y', pattern, rows, colums);
				printEl((i - pattern) + 1, 'r', pattern, rows, colums);
				Sleep(speed / 2);
			}
			printEl(i - pattern, 'w', pattern, rows, colums);
			printEl((i - pattern) + 1, 'r', pattern, rows, colums);
			Sleep(speed / 2);
		}
		printEl((end - pattern), 'g', pattern, rows, colums);
		--end;
	}
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
	printMat(mat, rows, colums, 0, 0);
	Sleep(speed);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void shakerSort(int** mat, int** pattern, int rows, int colums, int speed) {
	system("cls");
	printMat(mat, rows, colums, 0, 0);
	bool isChanged = true;
	int x, y, el;
	int** start = pattern, ** end = &pattern[rows * colums - 1];
	while (isChanged == true) {
		isChanged = false;
		for (int** i = start; i < end; ++i) {
			printEl(i - pattern, 'r', pattern, rows, colums);
			printEl((i - pattern) + 1, 'y', pattern, rows, colums);
			Sleep(speed / 2);
			if (**(i + 1) < **i) {
				swap(**(i + 1), **i);
				isChanged = true;

				printEl(i - pattern, 'y', pattern, rows, colums);
				printEl((i - pattern) + 1, 'r', pattern, rows, colums);
				Sleep(speed / 2);
			}
			printEl(i - pattern, 'w', pattern, rows, colums);
			printEl((i - pattern) + 1, 'r', pattern, rows, colums);
			Sleep(speed / 2);
		}
		printEl(end - pattern, 'g', pattern, rows, colums);
		--end;
		if (!isChanged) {
			break;
		}
		for (int** i = end; i > start; --i) {
			printEl(i - pattern, 'r', pattern, rows, colums);
			printEl((i - pattern) - 1, 'y', pattern, rows, colums);
			Sleep(speed / 2);
			if (**i < **(i - 1)) {
				swap(**i, **(i - 1));
				isChanged = true;

				printEl(i - pattern, 'y', pattern, rows, colums);
				printEl((i - pattern) - 1, 'r', pattern, rows, colums);
				Sleep(speed / 2);
			}
			printEl(i - pattern, 'w', pattern, rows, colums);
			printEl((i - pattern) - 1, 'r', pattern, rows, colums);
			Sleep(speed / 2);
		}
		printEl(start - pattern, 'g', pattern, rows, colums);
		++start;
	}
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
	printMat(mat, rows, colums, 0, 0);
	Sleep(speed);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void combSort(int** mat, int** pattern, int rows, int colums, int speed) {
	system("cls");
	printMat(mat, rows, colums, 0, 0);
	int x, y, el;
	float k = 1.247;
	bool isChanged = true;
	int** end = &pattern[rows * colums - 1], gap = rows * colums - 1;
	while (gap != 1) {
		for (int** i = pattern; i - pattern < (end - pattern) + 1 - gap; ++i) {

			printEl(i - pattern, 'r', pattern, rows, colums);
			printEl((i - pattern) + gap, 'b', pattern, rows, colums);
			Sleep(speed / 2);

			if (**i > **(i + gap)) {
				swap(**(i + gap), **i);
				printEl(i - pattern, 'b', pattern, rows, colums);
				printEl((i - pattern) + gap, 'r', pattern, rows, colums);
				Sleep(speed / 2);
			}

			Sleep(speed / 2);
			printEl(i - pattern, 'w', pattern, rows, colums);
			printEl((i - pattern) + gap, 'w', pattern, rows, colums);
		}
		gap /= k;
	}

	while (isChanged == true) {
		isChanged = false;
		for (int** i = pattern; i < end; ++i) {
			printEl(i - pattern, 'r', pattern, rows, colums);
			printEl((i - pattern) + 1, 'y', pattern, rows, colums);
			Sleep(speed / 2);
			if (**(i + 1) < **i) {
				swap(**(i + 1), **i);
				isChanged = true;

				printEl(i - pattern, 'y', pattern, rows, colums);
				printEl((i - pattern) + 1, 'r', pattern, rows, colums);
				Sleep(speed / 2);
			}
			printEl(i - pattern, 'w', pattern, rows, colums);
			printEl((i - pattern) + 1, 'r', pattern, rows, colums);
			Sleep(speed / 2);
		}
		--end;
	}
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
	printMat(mat, rows, colums, 0, 0);
	Sleep(speed);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void insertSort(int** mat, int** pattern, int rows, int colums, int speed) {
	system("cls");
	printMat(mat, rows, colums, 0, 0);
	int x, y, el;
	int** end = &pattern[rows * colums - 1], stepCount;
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
	for (int** start = pattern + 1; start <= end; ++start) {
		stepCount = 0;
		while (*(start - stepCount) != pattern[0] && **(start - stepCount) < **(start - 1 - stepCount)) {
			swap(**(start - stepCount), **(start - 1 - stepCount));

			printEl((start - pattern) - stepCount, 'g', pattern, rows, colums);
			printEl((start - pattern) - 1 - stepCount, 'r', pattern, rows, colums);
			Sleep(speed);
			++stepCount;
		}
		printEl((start - pattern) - stepCount, 'g', pattern, rows, colums);
		if (*(start - stepCount) != pattern[0]) {
			printEl((start - pattern) - 1 - stepCount, 'g', pattern, rows, colums);
		}
		Sleep(speed);

	}
}

void quickSortSep(int** pattern, int colums, int rows, int** start, int** end, int speed) {
	int el, x, y;
	int** pivot = start;
	++start;
	for (int** i = pattern; i < pivot; ++i) {
		printEl(i - pattern, 'g', pattern, rows, colums);
	}

	if (start >= end) {
		return;
	}

	printEl(pivot - pattern, 'b', pattern, rows, colums);
	Sleep(speed / 2);

	for (int** i = start; i <= end; ++i) {

		printEl(i - pattern, 'r', pattern, rows, colums);
		Sleep(speed / 2);

		if (**i < **pivot) {
			swap(**i, **start);

			printEl(start - pattern, 'y', pattern, rows, colums);

			++start;
		}
		if (start - 1 != i && i != end) {
			printEl(i - pattern, 'v', pattern, rows, colums);
		}
		else if (start - 1 != i && i - pattern == rows * colums - 1) {
			printEl(i - pattern, 'w', pattern, rows, colums);
		}
		else if (start - 1 != i) {
			printEl(i - pattern, 'g', pattern, rows, colums);
		}
		Sleep(speed / 2);
	}
	swap(**pivot, **(start - 1));

	for (int** i = pivot; i < end; ++i) {
		printEl(i - pattern, 'w', pattern, rows, colums);
	}
	printEl((start - pattern) - 1, 'g', pattern, rows, colums);

	quickSortSep(pattern, colums, rows, pivot, start - 1, speed);
	quickSortSep(pattern, colums, rows, start, end, speed);
}

void quickSortMain(int** mat, int** pattern, int rows, int colums, int speed) {
	system("cls");
	printMat(mat, rows, colums, 0, 0);
	quickSortSep(pattern, colums, rows, pattern, pattern + (rows * colums - 1), speed);
}

void mergeSortStep(int** pattern, int rows, int colums, int start, int end, int twoSortArr[], int speed) {
	int parity = (end - start + 1) % 2;
	for (int i = start; i <= end; ++i) {
		printEl(i, 'y', pattern, rows, colums);
	}
	Sleep(speed * 2);
	if (end - start <= 1) {
		if (end - start == 1 && *pattern[end] < *pattern[start]) {
			printEl(start, 'v', pattern, rows, colums);
			printEl(end, 'r', pattern, rows, colums);
			Sleep(speed);
			swap(*pattern[start], *pattern[end]);
			printEl(start, 'r', pattern, rows, colums);
			printEl(end, 'v', pattern, rows, colums);
			Sleep(speed);
			printEl(start, 'w', pattern, rows, colums);
			printEl(end, 'w', pattern, rows, colums);
		}
		for (int i = start; i <= end; ++i) {
			printEl(i, 'w', pattern, rows, colums);
		}
		return;
	}
	for (int i = start; i <= end; ++i) {
		printEl(i, 'w', pattern, rows, colums);
	}
	Sleep(speed);
	mergeSortStep(pattern, rows, colums, start, (end + start) / 2 - parity, twoSortArr, speed);
	mergeSortStep(pattern, rows, colums, (end + start) / 2 + 1 - parity, end, twoSortArr, speed);
	int ind = 0;
	int lArrIndex = start, rArrIndex = (end + start) / 2 + 1 - parity;
	for (int i = start; i <= (end + start) / 2 - parity; ++i) {
		printEl(i, 'v', pattern, rows, colums);
	}
	for (int i = (end + start) / 2 + 1 - parity; i <= end; ++i) {
		printEl(i, 'r', pattern, rows, colums);
	}
	Sleep(speed * 3);
	for (int i = 0; i <= end - start; ++i) {
		if (lArrIndex <= (end + start) / 2 - parity && rArrIndex <= end) {
			if (*pattern[lArrIndex] > *pattern[rArrIndex]) {
				twoSortArr[ind] = *pattern[rArrIndex];
				++rArrIndex;
				++ind;
				printEl(i + start, 'r', pattern, rows, colums);
			}
			else {
				twoSortArr[ind] = *pattern[lArrIndex];
				++lArrIndex;
				++ind;
				printEl(i + start, 'v', pattern, rows, colums);
			}
		}
		else if (rArrIndex > end) {
			twoSortArr[ind] = *pattern[lArrIndex];
			++lArrIndex;
			++ind;
			printEl(i + start, 'v', pattern, rows, colums);
		}
		else {
			twoSortArr[ind] = *pattern[rArrIndex];
			++rArrIndex;
			++ind;
			printEl(i + start, 'r', pattern, rows, colums);
		}
	}
	Sleep(speed * 3);
	ind = 0;
	for (int i = start; i <= end; ++i) {
		*pattern[i] = twoSortArr[ind];
		++ind;
	}
	for (int i = start; i <= end; ++i) {
		printEl(i, 'g', pattern, rows, colums);
	}
	Sleep(speed);
}

void mergeSortMain(int** mat, int** pattern, int rows, int colums, int speed) {
	system("cls");
	printMat(mat, rows, colums, 0, 0);
	int* twoSortArr = new int[rows * colums];
	mergeSortStep(pattern, rows, colums, 0, rows * colums - 1, twoSortArr, speed);
	delete[] twoSortArr;
}

void multiplicationMat(int* firstArr, int** mat, int rows, int& colums, int secondMatColums, int speed) {
	system("cls");
	int** secondMat = new int* [colums];
	int* secondArr = new int[colums * secondMatColums];
	for (int i = 0; i < colums; i++) {
		secondMat[i] = secondArr + i * secondMatColums;
	}
	srand(time(0));
	for (int i = 0; i < colums * secondMatColums; ++i) {
		secondArr[i] = rand() % (colums * secondMatColums) + 1;
	}

	printMat(mat, rows, colums, 0, 0);
	destCoord.X = (colums + 1) * 5;
	destCoord.Y = rows / 2;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "*" << '\r';
	cout.flush();
	printMat(secondMat, rows, secondMatColums, (colums + 2) * 5, 0);

	destCoord.X = (colums + 3 + secondMatColums) * 5;
	destCoord.Y = rows / 2;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "=" << '\r';
	cout.flush();

	int** multipMat = new int* [rows];
	int* multipArr = new int[rows * secondMatColums];
	for (int i = 0; i < rows; i++) {
		multipMat[i] = multipArr + i * secondMatColums;
	}
	for (int i = 0; i < rows * secondMatColums; ++i) {
		multipArr[i] = 0;
	}

	int* firP = &mat[0][0], * secP = secondArr, * mulP = multipArr;
	int x = (colums + 4 + secondMatColums) * 5, y = 0;
	int c;
	for (; mulP - multipArr < rows * secondMatColums; ++mulP) {

		for (int i = 0; i < colums; ++firP, secP += secondMatColums, ++i) {
			*mulP += (*firP) * (*secP);
			c = 1;
		}
		secP += 1 - secondMatColums * colums;
		firP -= colums;
		printNumber(*mulP, x, y);
		if ((mulP - multipArr + 1) % secondMatColums == 0) {
			firP += colums;
			y++;
			secP -= secondMatColums;
			x -= secondMatColums * 5;

		}
		x += 5;
		Sleep(speed * 2);
	}

	if (firstArr) {
		delete[] firstArr;
	}
	delete[] secondArr;
	int* arr = new int[rows * secondMatColums];
	for (int i = 0; i < rows; i++) {
		mat[i] = arr + i * secondMatColums;
	}
	for (int i = 0; i < rows * secondMatColums; i++) {
		arr[i] = multipArr[i];
	}
	delete[] multipArr;
	delete[] secondMat;
	delete[] multipMat;
	colums = secondMatColums;
}

int thirdPractic() {
	system("cls");
	setlocale(0, "");
	int rows, colums, secondMatColums, number;
	int speed = 100;
	int choice = 0;
	cout << "Введите через пробел кол-во строк и столбцов:\n";
	cin >> rows >> colums;
	int** mat = new int* [rows];
	int* arr = new int[rows * colums];
	int** pattern = new int* [rows * colums];
	for (int i = 0; i < rows; i++) {
		mat[i] = arr + i * colums;
	}
	for (int i = 0; i < rows * colums; ++i) {
		arr[i] = 0;
	}
	do {
		system("cls");
		cout << "Ваша матрица:";
		printMat(mat, rows, colums, 0, 1);
		cout << "\nДействия:\n"
			<< "1) Заполнить\n"
			<< "2) Переставить блоки\n"
			<< "3) Увеличить/уменьшить все элементы в/на n раз/число\n"
			<< "4) Отсортировать\n"
			<< "5) Умножить на другую матрицу\n"
			<< "6) Изменить скорость отрисовки\n"
			<< "-1) Закончить программу\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1: // Заполнить
			do {
				cout << "Выберите способ заполнения матрицы:\n"
					<< "1) По спирали\n"
					<< "2) По вертикали\n"
					<< "3) Слева направо\n"
					<< "0) Назад\n";
				cin >> choice;
				switch (choice) {
				case 1:
					fillMatSpiral(mat, rows, colums, speed);
					break;
				case 2:
					fillMatVert(mat, rows, colums, speed);
					break;
				case 3:
					fillMatSimple(mat, rows, colums, speed);
					break;
				}
			} while (choice != 0);
			break;
		case 2: // Переставить блоки
			do {
				cout << "Как переставить блоки?:\n"
					<< "1) По кругу\n"
					<< "2) Наискось\n"
					<< "3) По вертикали\n"
					<< "4) По горизонтали\n"
					<< "0) Назад\n";
				cin >> choice;
				system("cls");
				cout << "старая матрица";
				printMat(mat, rows, colums, 0, 1);
				switch (choice) {
				case 1:
					replaceBlocksRound(mat, rows, colums);
					break;
				case 2:
					replaceBlocksObliq(mat, rows, colums);
					break;
				case 3:
					replaceBlocksVert(mat, rows, colums);
					break;
				case 4:
					replaceBlocksHor(mat, rows, colums);
					break;
				}
				cout << "\nновая матрица";
				printMat(mat, rows, colums, 0, rows + 2);
				cout << endl;
			} while (choice != 0);
			break;
		case 3: // Увеличить/уменьшить все элементы в/на n раз/число
			cout << "Введите число:\n";
			cin >> number;
			do {
				cout << "\nДействия:\n"
					<< "1) Прибавить " << number << "\n"
					<< "2) Отнять " << number << "\n"
					<< "3) Умножить на " << number << "\n"
					<< "4) Разделить на " << number << "\n"
					<< "5) Изменить число\n"
					<< "0) Назад\n";
				cin >> choice;
				if (choice != 5) {
					system("cls");
					cout << "старая матрица";
					printMat(mat, rows, colums, 0, 1);
					switch (choice) {
					case 0:
						break;
					case 1:
						arithOperMat(mat, rows, colums, '+', number);
						break;
					case 2:
						arithOperMat(mat, rows, colums, '-', number);
						break;
					case 3:
						arithOperMat(mat, rows, colums, '*', number);
						break;
					case 4:
						arithOperMat(mat, rows, colums, '/', number);
						break;
					}
					cout << "\nновая матрица";
					printMat(mat, rows, colums, 0, rows + 2);
					cout << endl;
				}
				else {
					system("cls");
					cout << "Введите число:\n";
					cin >> number;
				}
			} while (choice != 0);
			break;
		case 4: // Отсортировать
			do {
				system("cls");
				cout << "Ваша матрица:";
				printMat(mat, rows, colums, 0, 1);
				cout << "\nКак отсортировать?:\n"
					<< "1) Спиралью\n"
					<< "2) Вертикально(вниз-вверх-вниз-...)\n"
					<< "3) Слева направо\n"
					<< "0) Назад\n";
				cin >> choice;
				switch (choice) {
				case 1:
					createSpiralPointersPattern(pattern, mat, rows, colums);
					break;
				case 2:
					createVertPointersPattern(pattern, mat, rows, colums);
					break;
				case 3:
					createVertPointersSimple(pattern, mat, rows, colums);
					break;
				}
				if (0 < choice < 4) {
					break;
				}
			} while (choice != 0);
			while (choice != 0) {
				system("cls");
				cout << "Ваша матрица:";
				printMat(mat, rows, colums, 0, 1);
				cout << "\nКакую сортировку использовать?:\n"
					<< "1) Bubble sort\n"
					<< "2) Shaker sort\n"
					<< "3) Comb sort\n"
					<< "4) Insert sort\n"
					<< "5) Quck sort\n"
					<< "6) Merge sort\n"
					<< "0) Назад\n";
				cin >> choice;
				switch (choice) {
				case 1:
					bubbleSort(mat, pattern, rows, colums, speed);
					break;
				case 2:
					shakerSort(mat, pattern, rows, colums, speed);
					break;
				case 3:
					combSort(mat, pattern, rows, colums, speed);
					break;
				case 4:
					insertSort(mat, pattern, rows, colums, speed);
					break;
				case 5:
					quickSortMain(mat, pattern, rows, colums, speed);
					break;
				case 6:
					mergeSortMain(mat, pattern, rows, colums, speed);
					break;
				}
			}
			break;
		case 5: // Умножить на другую матрицу
			cout << "Введите кол-во стобцов матрицы на которую будете умножать :  ";
			cin >> secondMatColums;
			multiplicationMat(arr, mat, rows, colums, secondMatColums, speed);
			arr = &mat[0][0];
			break;
		case 6: // Изменить скорость отрисовки
			cout << "нынешнее значение : " << speed << "\n";
			cout << "Введите желаемое значение(0 - очень быстро 200< - очень медленно ) :  ";
			cin >> speed;
			break;
		}
	} while (choice != -1);
	delete[] arr;
	delete[] mat;
	return 0;
}

char* inputString(char* string) {
	cin.clear();
	int count = 0;
	char symbol;
	cin >> symbol;
	while (symbol != '\n') {
		string[count] = symbol;
		count++;
		string = (char*)realloc(string, (2 + count) * sizeof(char));
		cin.get(symbol);
	}
	string[count] = '\0';
	cout << string << endl;
	return string;
}

int lengthStr(char* string) {
	int count = 0;
	while (string[count]) {
		count++;
	}
	return count;
}

char* replaceStringElements(char* string, const char sourceStr[], int sourceStrlength, const char finalyStr[], int finalyStrlength) {
	int stringlength = lengthStr(string);
	bool flag;
	for (int i = 0; i < stringlength + 1 - sourceStrlength; ++i) {
		flag = true;
		for (int k = 0; k < sourceStrlength; k++) {
			if (string[i + k] != sourceStr[k]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			if (sourceStrlength != finalyStrlength) {
				char* s = new char[stringlength + 1 - i];
				for (char* j = &string[i + sourceStrlength]; *j != '\0'; ++j) {
					*(s + (j - &string[i + sourceStrlength])) = *j;
				}
				s[stringlength - sourceStrlength - i] = '\0';
				string = (char*)realloc(string, (stringlength - sourceStrlength + finalyStrlength) * sizeof(char));
				string[stringlength - sourceStrlength + finalyStrlength] = '\0';
				for (char* j = &string[i + finalyStrlength]; *j != '\0'; ++j) {
					*j = *(s + (j - &string[i + finalyStrlength]));
				}
				delete[] s;
			}
			for (char* j = &string[i]; j < string + i + finalyStrlength; ++j) {
				*j = *(finalyStr + (j - &string[i]));
			}
			stringlength = lengthStr(string);
			i--;
		}
	}
	return string;
}

void checkRegister(char* string) {
	int stringlength = lengthStr(string);
	for (char* i = string; i < (string + stringlength - 1); ++i) {
		if (isalpha(*(i), locale("Russian")) && isupper(*(i + 1), locale("Russian"))) {
			*(i + 1) = tolower(*(i + 1), locale("Russian"));
		}
	}
}

char* readFile(char* string, char* fileName) {
	setlocale(LC_ALL, "Russian");
	ifstream file;
	char symb = ' ';
	int count = 0;
	int lastGcount = -1;
	int g = 0;
	file.open(fileName);
	if (!file.is_open()) {
		cout << "Файл не открыт\0";
		return string;
	}
	else {
		do {
			file.get(symb);
			string = (char*)realloc(string, (3 + count) * sizeof(char));
			string[count] = symb;
			count++;
		} while (file.gcount() != 0);
		count -= 1;
		string = (char*)realloc(string, (3 + count) * sizeof(char));
		string[count] = '\0';
		return string;
	}
}

char* firstWord(char* string) {
	char* newStr = new char[1];
	int last;
	int lengthString = lengthStr(string),
		lengthNewString = 1;
	bool checkWord;
	for (int i = 0, count = 1; i < lengthString; i += count, count = 1) {
		checkWord = false;
		while (string[i + count - 1] != ' ' && string[i + count - 1] != '\0') {
			if (tolower(string[i + count]) == tolower(string[i])) {
				checkWord = true;
			}
			count++;
		}
		if (checkWord) {
			newStr = (char*)realloc(newStr, (lengthNewString + count) * sizeof(char));
			last = lengthNewString - 1;
			lengthNewString += count;
			count = 1;
			newStr[count - 2 + last] = ' ';
			while (string[i + count - 1] != ' ' && string[i + count - 1] != '\0') {
				newStr[count - 1 + last] = string[i + count - 1];
				count++;
			}
		}
	}
	newStr[lengthNewString - 1] = '\0';
	return newStr;
}

char* deleteSymb(char* string) {
	system("cls");
	char* newStr = new char[1];
	cout << "Введите набор букв и (или) цифр бeз пробелов\n";
	newStr = inputString(newStr);
	for (int i = 0; newStr[i] != '\0'; i++) {
		const char* symb = &newStr[i];
		string = replaceStringElements(string, symb, 1, "", 0);
	}
	delete[] newStr;
	return string;
}

void findSubstringLinear(char* string, char* substring) {
	int count;
	bool check;
	for (int i = 0; string[i] != '\0'; i++) {
		count = 0;
		for (int j = 0; substring[j] != '\0'; j++) {
			if (substring[j] == string[i + count]) {
				count++;
				check = true;
			}
			else {
				check = false;
				break;
			}
		}
		if (check) {
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			cout << substring;
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			i += count - 1;
		}
		else {
			cout << string[i];
		}
	}
}

void findSubstringKMP(char* string, char* substring) {
	int stringLength = lengthStr(string),
		substringLength = lengthStr(substring);
	int* prefArr = new int[substringLength];
	prefArr[0] = 0;
	int last = 0;
	for (int i = 1, j = 0; i < substringLength;) {
		if (substring[i] == substring[j]) {
			prefArr[i] = j + 1;
			i++;
			j++;
		}
		else {
			if (j == 0) {
				prefArr[i] = 0;
				i++;
			}
			else {
				j = prefArr[j - 1];
			}
		}
	}
	for (int i = 0, j = 0; i < stringLength;) {
		if (string[i] == substring[j]) {
			i++;
			j++;
			if (j == substringLength) {
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
				cout << substring;
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				last = i + 1;
			}
		}
		else {
			if (j == 0) {
				i++;
				for (int k = last; k < i; k++) {
					cout << string[k];
				}
				last = i;
			}
			else {
				j = prefArr[j - 1];
				for (int k = last; k < i - prefArr[j]; k++) {
					cout << string[k];
				}
				last = i - prefArr[j];
			}
		}
	}
	delete[] prefArr;
}

void findSubstringBM(char* string, char* substring) {
	int stringLength = lengthStr(string),
		substringLength = lengthStr(substring);
	bool check = false;
	int count = substringLength;
	int last = 0;
	map<char, int> shiftMap;
	for (int i = 1; i < substringLength; ++i) {
		shiftMap[substring[i - 1]] = substringLength - i;
	}
	if (!shiftMap.count(string[substringLength - 1])) {
		shiftMap[substring[substringLength - 1]] = substringLength;
	}
	for (int i = substringLength - 1; i < stringLength;) {
		for (int j = i; j > i - substringLength; --j) {
			if (string[j] == substring[substringLength - 1 - (i - j)]) {
				check = true;
			}
			else {
				check = false;
				if (shiftMap.count(string[j])) {
					for (int k = last; k < i - substringLength + shiftMap[string[j]] + 1; k++) {
						cout << string[k];
					}
					last = i - substringLength + shiftMap[string[j]] + 1;
					i += shiftMap[string[j]];
				}
				else {
					for (int k = last; k < i + 1; k++) {
						cout << string[k];
					}
					last = i + 1;
					i += substringLength;
				}
				break;
			}
		}
		if (check) {
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			cout << substring;
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			last = i + 1;
			i += substringLength;
		}
		if (i > stringLength) {
			for (int k = last; string[k] != '\0'; k++) {
				cout << string[k];
			}
		}
	}
}

int hashString(char* string) {
	int result = *string;
	for (char* i = string; *(i + 1) != '\0'; ++i) {
		result = (result << 5) + *(i + 1);
	}
	return result % 2147483647;
}

void findSubstringRK(char* string, char* substring) {
	int stringLength = lengthStr(string),
		substringLength = lengthStr(substring);
	int substringHash = hashString(substring);
	char* s = new char[substringLength+1];
	for (int i = 0; i < substringLength; i++) {
		s[i] = string[i];
	}
	s[substringLength] = '\0';
	int actualHash = hashString(s);
	delete[] s;
	bool check;
	for (int i = 0; i <= stringLength - substringLength;) {
		if (substringHash == actualHash) {
			check = false;
			for (int j = 0; j < substringLength; j++) {
				if (substring[j] == string[i + j]) {
					check = true;
				}
				else {
					check = false;
					break;
				}
			}
			if (check) {
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
				cout << substring;
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				for (int j = 0; j < substringLength; j++) {
					actualHash = (((actualHash - (string[i] << (5 * (substringLength - 1)))) << 5) + string[i + substringLength]) % 2147483647;
					i++;
				}
			}
			else {
				cout << string[i];
				actualHash = (((actualHash - (string[i] << (5 * (substringLength - 1)))) << 5) + string[i + substringLength]) % 2147483647;
				i++;
			}
		}
		else {
			cout << string[i];
			actualHash = (((actualHash - (string[i] << (5 * (substringLength - 1)))) << 5) + string[i + substringLength]) % 2147483647;
			i++;
		}
	}
	for (int i = stringLength - substringLength + 1; i < stringLength; i++) {
		cout << string[i];
	}
}

void findSubstringHashMap(char* string, char* substring) {
	int stringLength = lengthStr(string),
		substringLength = lengthStr(substring);
	map<char, int *> hashMap;
	for (int i = 0; i < stringLength; i++) {
		if (hashMap.count(string[i])) {
			for (int j = 0; j < stringLength; ++j) {
				if (hashMap[string[i]][j] == -1) {
					hashMap[string[i]][j] = i;
					break;
				}
			}
		}
		else {
			hashMap[string[i]] = new int[stringLength];
			for (int j = 0; j < stringLength; ++j) {
				hashMap[string[i]][j] = -1;
			}
			hashMap[string[i]][0] = i;
		}
	}
	bool check;
	int last = 0;
	int a,b;
	for (int i = 0; hashMap[substring[0]][i] != -1; i++) {
		check = false;
		a = hashMap[substring[0]][i];
		b = hashMap[substring[0]][i+1];
		for (int j = hashMap[substring[0]][i]; j < hashMap[substring[0]][i] + substringLength; ++j) {
			if (string[j] == substring[j - hashMap[substring[0]][i]]) {
				check = true;
			}
			else {
				check = false;
				break;
			}
		}
		if (check) {
			for (int j = last; j < hashMap[substring[0]][i]; j++) {
				cout << string[j];
			}
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			cout << substring;
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			last = hashMap[substring[0]][i] + substringLength;
		}
	}
	for (int j = last; j < stringLength; j++) {
		cout << string[j];
	}
}

int fourthPractic() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "Russian");
	int choise;
	char* string = new char[2];
	bool isInputed = false;
	char fileName[] = "string.txt";
	char* substring = new char[1];
	do {
		if (isInputed) {
			system("cls");
			do {
				cout << "Сткрока:\n" << string << endl;
				cout << "Доступные действия:\n"
					<< "1) Ввести новую строку\n"
					<< "2) Отредактировать строку\n"
					<< "3) Вывести на экран только те слова последовательности, в которых первая буква слова встречается в этом слове еще раз\n"
					<< "4) Вывести на экран ту же последовательность, удалив из всех слов заданный набор букв и (или) цифр\n"
					<< "5) Найти подстроку\n"
					<< "-1) Назад\n";
				cin >> choise;
				switch (choise) {
				case 1:
					do {
						system("cls");
						cout << "Способ ввода строки:\n"
							<< "1) вручную\n"
							<< "2) через файл 'string'\n";
						cin >> choise;
						switch (choise) {
						case 1:
							system("cls");
							cout << "Введите строку:\n";
							string = inputString(string);
							break;
						case 2:
							string = readFile(string, fileName);
							break;
						}
					} while (!(choise == 1 || choise == 2));
					break;
				case 2:
					system("cls");
					string = replaceStringElements(string, "  ", 2, " ", 1);
					string = replaceStringElements(string, ",,", 2, ",", 1);
					string = replaceStringElements(string, "....", 4, "...", 3);
					string = replaceStringElements(string, "...", 3, "\n", 1);
					string = replaceStringElements(string, "..", 2, ".", 1);
					string = replaceStringElements(string, "\n", 1, "...", 3);
					string = replaceStringElements(string, "::", 2, ":", 1);
					string = replaceStringElements(string, "??", 2, "?", 1);
					string = replaceStringElements(string, "!!", 2, "!", 1);
					string = replaceStringElements(string, ";;", 2, ";", 1);
					string = replaceStringElements(string, "--", 2, "-", 1);
					string = replaceStringElements(string, "((", 2, "(", 1);
					string = replaceStringElements(string, "))", 2, ")", 1);
					string = replaceStringElements(string, "\"\"", 2, "\"", 1);
					checkRegister(string);
					break;
				case 3:
					system("cls");
					cout << firstWord(string) << endl;
					break;
				case 4:
					system("cls");
					string = deleteSymb(string);
					system("cls");
					break;
				case 5:
					system("cls");
					cout << "Введите подстроку:\n";
					substring = inputString(substring);
					system("cls");
					do {
						cout << "Подстрока: " << substring << endl
							<< "Выберите способ поиска  подстроки:\n"
							<< "1) Линейный поиск\n"
							<< "2) Алгоритм Кнута-Мориса-Прата\n"
							<< "3) Алгоритм Боера-Мура\n"
							<< "4) Алгоритм Рабина-Карпа\n"
							<< "5) Через хэш таблицу?\n"
							<< "0) Назад\n";
						cin >> choise;
						switch (choise) {
						case 1:
							system("cls");
							findSubstringLinear(string, substring);
							cout << endl;
							break;
						case 2:
							system("cls");
							findSubstringKMP(string, substring);
							cout << endl;
							break;
						case 3:
							system("cls");
							findSubstringBM(string, substring);
							cout << endl;
							break;
						case 4:
							system("cls");
							findSubstringRK(string, substring);
							cout << endl;
							break;
						case 5:
							system("cls");
							findSubstringHashMap(string, substring);
							cout << endl;
							break;
						}
					} while (choise != 0);
					break;
				}
			} while (choise != -1);
		}
		else {
			cout << "Способ ввода строки:\n"
				<< "1) вручную\n"
				<< "2) через файл 'string'\n";
			isInputed = true;
			do {
				cin >> choise;
				switch (choise) {
				case 1:
					system("cls");
					cout << "Введите строку:\n";
					string = inputString(string);
					break;
				case 2:
					string = readFile(string, fileName);
					break;
				}
			} while (!(choise == 1 || choise == 2));
		}
	} while (choise != -1);

	delete[] string;
	return 0;
}

int main(){
    int choise;
	setlocale(0, "");
    do {
		system("cls");
		cout << "Выберите практическую работу:\n"
			<< "1) Первая практическая\n"
			<< "2) Вторая практическая\n"
			<< "3) Третья практическая\n"
			<< "4) Четвёртая практическая\n"
			<< "-1) Выход\n";
        cin >> choise;
        switch(choise) {
        case 1:
            firstpPractic();
            break;
        case 2:
            secondPractic();
            break;
        case 3:
			thirdPractic();
            break;
        case 4:
			fourthPractic();
            break;
        }
    } while (choise != -1);
}
