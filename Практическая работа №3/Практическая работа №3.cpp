#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

template<const int sizeMat>
void printMat(int mat[][sizeMat], int* turtle) {
	cout << endl;
	for (int i = 0; i < sizeMat; ++i) {
		for (int j = 0; j < sizeMat; ++j) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (turtle == &mat[j][i]) {
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				cout << setw(3) << '@' << ' ';
			}
			else {
				if (mat[j][i] != 0) {
					SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
				}
				cout << setw(3) << mat[j][i] << ' ';
			}
		}
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << endl;
	}
}

int main(){
	setlocale(0, "");
	const int sizeMat = 10;
	int mat[sizeMat][sizeMat], c=1;
	for (int i = 0; i < sizeMat; ++i) {
		for (int j = 0; j < sizeMat; ++j) {
			mat[j][i] = 0;
			cout << setw(3) << mat[j][i] << ' ';
		}
		cout << endl;
	}
	char side;
	int range, k = 0;
	char ;
	int* turtle = &mat[0][0];
	do {
		cout << "ввдете сторону(l/r/d/u) и дальность движения черепашки:\n";
		cin >> side >> range;
		switch (side) {
			case 'r':
				k = sizeMat;
				break;
			case 'l':
				k = -sizeMat;
				break;
			case 'u':
				k = -1;
				break;
			case 'd':
				k = 1;
				break;
		}
		for (int i = 0; i < range; ++i, ++c) {
			*turtle = c;
			turtle = turtle + k;
		}
		printMat<sizeMat>(mat, turtle);
	} while (side != 'n');
}