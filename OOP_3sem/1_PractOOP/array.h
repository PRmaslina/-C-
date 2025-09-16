#ifndef ARRAY_H
#define ARRAY_H

#include "number.h"

class Array
{
    int size;
    number* arr;
    
public:
    Array();
    Array(int newSize, number* newArr);
    ~Array();
    
    int getSize();
    number* changeSize(int newSize);
    void cinNumber(int place);
    void coutNumber(int place);
    number calcAverenge();
    number calcStandardDeviation();
    void sort(bool Direction = true);
};

#endif