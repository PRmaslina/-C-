#include <iomanip>
#include <iostream>
#include <chrono>
using namespace std;

void equatingMas(int arr[], int sourceArr[], const int sizeMas) {
    for (int i = 0; i < sizeMas; i++) {
        arr[i] = sourceArr[i];
    }
}

void bubbleSort(int arr[], const int sizeMas) {
    auto timeStart = chrono::steady_clock::now();
    bool isChanged = true;
    int end = sizeMas - 1;
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
    cout << "bubbleSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " sec\n";
    //    for (int i = 0; i < sizeMas; ++i) {
    //        cout << arr[i] << " ";
    //    }
}

void shakerSort(int arr[], const int sizeMas) {
    auto timeStart = chrono::steady_clock::now();
    bool isChanged = true;
    int start = 0, end = sizeMas - 1;
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
    cout << "shakerSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " sec\n";
    //    for (int i = 0; i < sizeMas; ++i) {
    //        cout << arr[i] << " ";
    //    }
}

void combSort(int arr[], const int sizeMas) {
    auto timeStart = chrono::steady_clock::now();

    float k = 1.247;
    bool isChanged = true;
    int gap = sizeMas - 1, end = sizeMas - 1;
    while (gap != 1) {
        for (int i = 0; i < sizeMas - gap; ++i) {
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
    cout << "combSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " sec\n";
    //    for (int i = 0; i < sizeMas; ++i) {
    //        cout << arr[i] << " ";
    //    }
}

void insertSort(int arr[], const int sizeMas) {
    auto timeStart = chrono::steady_clock::now();

    int end = sizeMas - 1, stepCount;
    for (int start = 1; start <= end; ++start){
        stepCount = 0;
        while (arr[start - stepCount] < arr[start - 1 - stepCount]){
            swap(arr[start - stepCount], arr[start - 1 - stepCount]);
            ++stepCount;
        }
    }
    auto timeEnd = chrono::steady_clock::now();
    cout << "insertSort  time:  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count() << " sec\n";
    //    for (int i = 0; i < sizeMas; ++i) {
    //        cout << arr[i] << " ";
    //    }
}

int main() {
    setlocale(0, "");
    const int sizeMas = 100;
    bool isChanged = true;
    int arr[sizeMas], sourceArr[sizeMas];
    cout << "Исходный массив: ";
    for (int i = 0; i < sizeMas; i++){
        sourceArr[i] = rand() % 1000;
        cout << sourceArr[i] << " ";
    }

    equatingMas(arr, sourceArr, sizeMas);
    cout << "\n\n";
    bubbleSort(arr, sizeMas);

    equatingMas(arr, sourceArr, sizeMas);
    cout << "\n\n";
    shakerSort(arr, sizeMas);

    equatingMas(arr, sourceArr, sizeMas);
    cout << "\n\n";
    combSort(arr, sizeMas);

    equatingMas(arr, sourceArr, sizeMas);
    cout << "\n\n";
    insertSort(arr, sizeMas);

    return 0;
}
