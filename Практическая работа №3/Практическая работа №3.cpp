#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

void prN(int number, int x, int y) {
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << setw(4) << number << '\r';
	cout.flush();
}

void printMat(int** mat, int rows, int colums, int x, int y) {
	//system("cls");
	int* turtle = &mat[0][0];
	for (int i = 1; i <= rows * colums; ++i, ++turtle, x+=4) {
		prN(*turtle, x, y);
		if (i % colums == 0){
			++y;
			x = -4;
		}
	}
}

void fillMatSpiral(int** mat, int rows, int colums) {
	system("cls");
	int* turtle = &mat[0][0];
	int k = 1, c = 1 , x = 0, y = 0;
	int f = 1, l = 1;
	bool flag = true;
	char side = 'r';
	while (c <= rows * colums){
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
			for (int i = 0; colums - l == 0 ? i <= colums - l : i < colums - l ; ++i, c++, side == 'd' ? x += 4 : x -= 4, turtle += k) {
				*turtle = c;//rand() % (rows*colums)  + 1;
				prN(*turtle, x, y);
				Sleep(100);
			}
			flag ? flag = false : l += 1;
		}
		else {
			for (int i = 0; rows - f == 0? i <= rows - f : i < rows - f; ++i, c++, side == 'l' ? y += 1 : y -= 1, turtle += k) {
				*turtle = c;//rand() % (rows*colums)  + 1;
				prN(*turtle, x, y);
				Sleep(100);
			}
			f += 1;
		}
	}
	destCoord.X = 0;
	destCoord.Y = rows+1;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void fillMatVert(int** mat, int rows, int colums) {
	system("cls");
	int* turtle = &mat[0][0];
	int k = 1, c = 1, x = 0, y = 0;
	char side = 'd';
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
			*turtle = c;//rand() % (rows*colums)  + 1;
			prN(*turtle, x, y);
			Sleep(100);
			side == 'u' ? y += 1 : y -= 1;
		}
		turtle++;
		x+=4;
		side == 'u' ? y -= 1 : y += 1;
		turtle-=k;
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

int main(){
	setlocale(0, "");
	int rows, colums;
	int choice = 0;
	cout << "Введите через пробел кол-во строк и стобцов:\n";
	cin >> rows >> colums;
	int** mat = new int*[rows];
	int* arr = new int [rows * colums];
	for (int i = 0; i < rows; i++){
		mat[i] = arr + i * colums;
	}
	for (int i = 0; i < rows * colums;++i) {
		arr[i] = 0;
	}
	do{
		system("cls");
		cout << "Ваша матрица:";
		printMat(mat, rows, colums, 0, 1);
		cout << "\nДействия:\n"
			<< "1) Заполнить\n"
			<< "2) Переставить блоки\n"
			<< "3) Увеличить/уменьшить все элементы в/на n раз/число\n"
			<< "4) Отсортировать\n"
			<< "5) Умножить на другую матрицу\n"
			<< "-1) Закончить программу\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:
			do {
				cout << "Выберите способ заполнения матрицы:\n"
					<< "1) По спирали\n"
					<< "2) По вертикали\n"
					<< "0) Назад\n";
				cin >> choice;
				switch (choice) {
				case 1:
					fillMatSpiral(mat, rows, colums);
					break;
				case 2:
					fillMatVert(mat, rows, colums);
					break;
				}
			} while (choice != 0);
			break;
		case 2:
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
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		}
	} while (choice != -1);
	//delete[] arr;
	cin >> rows;
	return 0;
}