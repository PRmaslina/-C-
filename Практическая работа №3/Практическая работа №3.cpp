#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

template<const int sizeMat>
void printMat(int mat[][sizeMat]) {
	cout << endl;
	for (int i = 0; i < sizeMat; ++i) {
		for (int j = 0; j < sizeMat; ++j) {
			if (mat[j][i] == 0) {
				cout << setw(3) << ' ' << ' ';
			}
			else {
				cout << setw(3) << mat[j][i] << ' ';
			}
		}
		cout << endl;
	}
}

int main(){
	setlocale(0, "");
	const int sizeMat = 15;
	int mat[sizeMat][sizeMat], c=1;
	for (int i = 0; i < sizeMat; ++i) {
		for (int j = 0; j < sizeMat; ++j) {
			mat[j][i] = 0;
			cout << setw(3) << mat[j][i] << ' ';
		}
		cout << endl;
	}
	char side = 'r';
	int k = 0;
	char ;
	int* turtle = &mat[0][0];
	do {
		cout << "ввдете сторону(l/r/d/u) и дальность движения черепашки:\n";
		//cin >> side >> range;
		//switch (side) {
		//case 'r':
		//	k = sizeMat;
		//	break;
		//case 'l':
		//	k = -sizeMat;
		//	break;
		//case 'u':
		//	k = -1;
		//	break;
		//case 'd':
		//	k = 1;
		//	break;
		//}
		for (int i = 0; i < sizeMat; ++i, ++c) {
			turtle += k;
			if (*turtle == 0) {
				*turtle = c;
			}
			else {
				turtle -= k;
				break;
			}
		}
		switch (side) {
			case 'r':
				k = sizeMat;
				side = 'd';
				break;
			case 'd':
				k = 1;
				side = 'l';
				break;
			case 'l':
				k = -sizeMat;
				side = 'u';
				break;
			case 'u':
				k = -1;
				side = 'r';
				break;
		}
		system("cls");
		printMat<sizeMat>(mat);
		Sleep(10);
	} while (side != 'n');
}