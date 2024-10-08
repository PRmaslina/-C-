#include <iostream>
#include <chrono>
using namespace std;

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
    for (int i = 0; i < sizeArr; i++) {
        arr[i] = (rand() % 100) - (rand() % 100);
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
    max = -sizeArr;
    min = sizeArr;
    for (int i = 0; i < sizeArr;++i) {
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
    for (int i = 0; i < sizeArr;++i) {
        if (arr[i] == average) {
            //cout << i << " ";
            ++count;
            flag = 1;
        }
        else if (flag == 1) {
            break;
        }
    }
    auto timeEnd1 = chrono::steady_clock::now();
    flag = 0;
    for (int i = 0; i < sizeArr;++i) {
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
    for (int i = 0; i < sizeArr;++i) {
        if (unsortArr[i] > max) {
            max = unsortArr[i];
        }
        if (unsortArr[i] < min) {
            min = unsortArr[i];
        }
    }
    average = (max + min) / 2;
    for (int i = 0; i < sizeArr;++i) {
        if (unsortArr[i] == average) {
            ++count;
        }
    }
    auto timeEnd2 = chrono::steady_clock::now();
    for (int i = 0; i < sizeArr;++i) {
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

int binarySearch(int arr[], int number, int start , int end) {
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
    else{
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
    else{
        cout << "ID этого элемента: " << idEl << endl;
    }
    cout << "Бинарный поиск  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";
    auto timeStart2 = chrono::steady_clock::now();
    idEl = simpleSearch(arr, number, sizeArr);
    auto timeEnd2 = chrono::steady_clock::now();
    if (idEl == -1) {
        cout << "Такого элемента нет в массиве\n";
    }
    else{
        cout << "ID этого элемента: " << idEl << endl;
    }
    cout << "Обычный поиск  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
}

void swapElTime(int arr[], int firstElId, int secondElId) {
    auto timeStart = chrono::steady_clock::now();
    swap(arr[firstElId], arr[secondElId]);
    auto timeEnd = chrono::steady_clock::now();
    cout << "swap time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

void bubbleSort(int arr[], const int sizeArr) {
    auto timeStart = chrono::steady_clock::now();
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
    auto timeEnd = chrono::steady_clock::now();
    cout << "bubbleSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

void shakerSort(int arr[], const int sizeArr) {
    auto timeStart = chrono::steady_clock::now();
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
    auto timeEnd = chrono::steady_clock::now();
    cout << "shakerSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

void combSort(int arr[], const int sizeArr) {
    auto timeStart = chrono::steady_clock::now();

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

    auto timeEnd = chrono::steady_clock::now();
    cout << "combSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

void insertSort(int arr[], const int sizeArr) {
    auto timeStart = chrono::steady_clock::now();

    int end = sizeArr - 1, stepCount;
    for (int start = 1; start <= end; ++start) {
        stepCount = 0;
        while (arr[start - stepCount] < arr[start - 1 - stepCount]) {
            swap(arr[start - stepCount], arr[start - 1 - stepCount]);
            ++stepCount;
        }
    }
    auto timeEnd = chrono::steady_clock::now();
    cout << "insertSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
}

//void quickSortSep(int arr[], int pivot,int &countEl) {
//    int smallArr[countEl / 2], largeArr[countEl / 2 + countEl % 2], smCount = 0, larCount = 0;
//    countEl /= 2;
//    if (countEl > 3) {
//        for (int i = 0; i < pivot; ++i) {
//            arr[i] < arr[pivot] ? smallArr[smCount++] = arr[i] : largeArr[larCount++] = arr[i];
//        }
//        pivot = sizeArr - 1;
//        quicksortsep(smallArr, pivot, countEl);
//        quicksortsep(largeArr, pivot, countEl);
//    }
//    else:
//}

//void quickSortMain(int arr[], const int sizeArr) {
//    auto timeStart = chrono::steady_clock::now();
//
//    int end = sizeArr - 1, pivot = sizeArr - 1, countEl = sizeArr;
//    while (countEl > 1) {
//        quicksortsep(arr, pivot, countEl);
//    }
//    
//
//    auto timeEnd = chrono::steady_clock::now();
//    cout << "insertSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " nanosec\n";
//    //    for (int i = 0; i < sizeArr; ++i) {
//    //        cout << arr[i] << " ";
//    //    }
//}

int main() {
    setlocale(0, "");
    const int sizeArr = 100;
    int choise, arr[sizeArr], unsortArr[sizeArr], inputNumber, firstElId, secondElId;
    arr[0] = 0;
    cout << "Исходный массив: ";
    createArr(unsortArr, sizeArr);
    printArr(unsortArr, sizeArr);
    do {
        if (arr[0] != 0) {
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
                arr[0] = 0;
                createArr(unsortArr, sizeArr);
                printArr(unsortArr, sizeArr);
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
                cin >> choise;
                switch (choise) {
                case 0:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    bubbleSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 1:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    shakerSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 2:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    combSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 3:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    insertSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 4:
                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n";
                    //quickSortMain(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 5:
                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n";
                    //quickSortMain(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 6:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    bubbleSort(arr, sizeArr);

                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    shakerSort(arr, sizeArr);

                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    combSort(arr, sizeArr);

                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    insertSort(arr, sizeArr);

                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n\n";
                    //quickSortMain(arr, sizeArr);

                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n\n";
                    //quickSortMain(arr, sizeArr);

                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                }
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
                break;
            }
        }
        else {
            cout << "\n\nВыберите нужный пункт:"
                << "\n 0) Переформировать массив"
                << "\n 1) Отсортировать массив"
                << "\n-1) Закончить выполнение программы\n";
            cin >> choise;
            switch (choise)
            {
            case(0): // Переформировать массвив  
                cout << "Новый исходный массив: ";
                arr[0] = 0;
                createArr(unsortArr, sizeArr);
                printArr(unsortArr, sizeArr);
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
                cin >> choise;
                switch (choise) {
                case 0:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    bubbleSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 1:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    shakerSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 2:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    combSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 3:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    insertSort(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 4:
                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n\n";
                    //quickSortMain(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 5:
                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n\n";
                    //quickSortMain(arr, sizeArr);
                    cout << "\nПолучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                case 6:
                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    bubbleSort(arr, sizeArr);

                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    shakerSort(arr, sizeArr);

                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    combSort(arr, sizeArr);

                    equatingArr(arr, unsortArr, sizeArr);
                    cout << "\n";
                    insertSort(arr, sizeArr);

                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n";
                    //quickSortMain(arr, sizeArr);

                    //equatingArr(arr, unsortArr, sizeArr);
                    //cout << "\n";
                    //quickSortMain(arr, sizeArr);

                    cout << "\nполучившийся массив: ";
                    printArr(arr, sizeArr);
                    break;
                }
                break;
            }
        }
    } while (choise != -1);
    return 0;
}
