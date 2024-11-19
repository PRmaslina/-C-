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
				Sleep(10);
			}
			flag ? flag = false : l += 1;
		}
		else {
			for (int i = 0; rows - f == 0? i <= rows - f : i < rows - f; ++i, c++, side == 'l' ? y += 1 : y -= 1, turtle += k) {
				*turtle = c;//rand() % (rows*colums)  + 1;
				prN(*turtle, x, y);
				Sleep(10);
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

void bubbleSort(int** mat, int rows, int colums) {
	system("cls");
	//printMat(mat, rows, colums, 0, 0);
	int x, y;
	bool isChanged = true;
	int el;
	int* end = &mat[rows - 1][colums - 1];
	while (isChanged == true) {
		isChanged = false;
		for (int* start = &mat[0][0]; start < end; ++start) {
			if (*(start + 1) < *start) {
				swap(*(start + 1), *start);
				isChanged = true;
			}
			el = start - &mat[0][0] + 1;
			x = (el == 1 ? 0 : (el % colums) * 4);
			y = (el == colums*rows? rows-1 : el / colums);
			prN(*start, x, y);
			el = &start[1] - &mat[0][0] + 1;
			x = (el == 1 ? 0 : (el % colums) * 4);
			y = (el == colums * rows? rows - 1 : el / colums);
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			prN(*(start + 1), x, y);
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			Sleep(100);
		}
		--end;
		//el = end - &mat[0][0] + 1;
		//x = (el == 1 ? 0 : (el % colums) * 4);
		//y = (el == colums * rows ? rows - 1 : el / colums);
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		prN(end[1], x, y);
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	cin >> rows;
	printMat(mat, rows, colums, 0, 0);
	cin >> rows;
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
	quickSortSep(arr, pivot, start - 2);
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

int main(){
	setlocale(0, "");
	int rows, colums, number = 0;
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
		case 1: // Заполнить
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
				if (choice != 5){
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
				cout << "\nКакую сортировку использовать?:\n"
					<< "1) Bubble sort\n"
					<< "2) Shaker sort\n"
					<< "3) Comb sort\n"
					<< "5) Insert sort\n"
					<< "6) Quck sort\n"
					<< "7) Merge sort\n"
					<< "0) Назад\n";
				cin >> choice;
				switch (choice) {
				case 1:
					bubbleSort( mat, rows, colums);
					break;
				case 2:
					
					break;
				case 3:
					
					break;
				case 4:
					
					break;
				case 5:

					break;
				case 6:

					break;
				case 7:

					break;
				}
			} while (choice != 0);
			break;
		case 5: // Умножить на другую матрицу

			break;
		}
	} while (choice != -1);
	//delete[] arr;
	cin >> rows;
	return 0;
}