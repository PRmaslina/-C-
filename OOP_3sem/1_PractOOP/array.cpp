#include <iostream>
#include <cmath>
#include "array.h"

Array::Array() {
    size = 0;
    arr = nullptr;
}

Array::Array(int newSize, number* newArr) {
    size = newSize;
    arr = new number[newSize];
    for(int i = 0; i < newSize; i++){
        arr[i] = newArr[i];
    }
}

Array::~Array() {
    delete[] arr;
}

int Array::getSize(){
    return size;
}

number* Array::changeSize(int newSize){
    number* newArr = new number[newSize];
    for(int i = 0; i < (newSize > size ? size : newSize) ; i++){
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size = newSize;
}

void Array::cinNumber(int place){
    std::cin >> arr[place];
}

void Array::coutNumber(int place){
    std::cout << arr[place];
}

number Array::calcAverenge(){
    number avr = 0;
    for(int i = 0; i < size; ++i){
        avr+=arr[i];
    }
    avr/= size;
    return avr;
}

number Array::calcStandardDeviation() {
    if (size == 0) 
        return 0;
    
    number average = calcAverenge();
    number sumSquaredDifferences = 0;
    
    for (int i = 0; i < size; i++) {
        number difference = arr[i] - average;
        sumSquaredDifferences += difference * difference;
    }
    
    number variance = sumSquaredDifferences / size;
    return sqrt(variance);
}

void Array::sort(bool Direction) {
    for (int start = 1; start < size; ++start) {
        int stepCount = 0;
        while (start - stepCount > 0 && (arr[start - stepCount] < arr[start - 1 - stepCount])) {
            std::swap(arr[start - stepCount], arr[start - 1 - stepCount]);
            ++stepCount;
        }
    }
}