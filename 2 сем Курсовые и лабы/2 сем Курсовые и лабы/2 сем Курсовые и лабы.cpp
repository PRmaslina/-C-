#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <chrono>

#include "stacks.h"

using namespace std;

int choiseMenu(string*, int, int, int);

void main() {
	setlocale(0, "");
	string expression;
	int choise = -1;
	cout << "Введите выражение (разделяйте числа и операторы пробелами):" << endl;
	getline(cin, expression);
	expression = ' ' + expression + ' ';
	while (choise != 4) {
		cout << expression << endl;
		system("cls");
		string menu[5] = { "1) Ввести заново                                    "
						 ,"2) Посчитать как обычное выражение                  "
						 ,"3) Посчитать в обратной польской нотации            "
						 ,"4) Посчитать в прямой польской нотации              "
						 ,"0) Выйти                                            " };
		bool UsualNot = thirdPract::checkUsualNot(expression),
			ReversePolNot = thirdPract::checkReversePolNot(expression),
			DirectPolNot = thirdPract::checkDirectPolNot(expression);
		if (!UsualNot) {
			menu[1] += "(недоступно)";
		}
		if (!ReversePolNot) {
			menu[2] += "(недоступно)";
		}
		if (!DirectPolNot) {
			menu[3] += "(недоступно)";
		}
		choise = choiseMenu(menu, 5, 0, 1);
		system("cls");
		switch (choise) {
		case 0:
			cout << "Введите выражение (разделяйте числа и операторы пробелами):" << endl;
			getline(cin, expression);
			expression = ' ' + expression + ' ';
			break;
		case 1:
			cout << thirdPract::solutionUsualNot(expression);
			getchar();
			break;
		case 2:
			thirdPract::solutionReversePolNot(expression);
			getchar();
			break;
		case 3:
			thirdPract::solutionDirectPolNot(expression);
			getchar();
			break;
		}
	}
}

int choiseMenu(string* menu, int countEl, int startX, int startY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;
	int choise = 0;
	int press = 0;
	int x = startX, y = startY;
	destCoord.Y = y;
	destCoord.X = x;
	for (int i = 0; i < countEl; ++i, ++y) {
		destCoord.Y = y;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << menu[i];
		cout.flush();
	}
	y = startY;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	SetConsoleTextAttribute(hStdout, 240);
	cout << "> " << menu[choise];
	SetConsoleTextAttribute(hStdout, 07 | FOREGROUND_INTENSITY);
	cout.flush();
	while (_getch() != 0x0D) {
		press = _getch();
		system("color 0F");
		switch (press) {
		case 0x48:
			destCoord.Y = y;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "   ";
			cout.flush();
			if (choise == 0) {
				choise = countEl - 1;
				y = startY + countEl - 1;
			}
			else {
				choise--;
				y--;
			}
			destCoord.Y = y;
			SetConsoleCursorPosition(hStdout, destCoord);
			SetConsoleTextAttribute(hStdout, 240);
			cout << "> " << menu[choise];
			SetConsoleTextAttribute(hStdout, 07 | FOREGROUND_INTENSITY);
			cout.flush();
			break;
		case 0x50:
			destCoord.X = x;
			destCoord.Y = y;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "   ";
			cout.flush();
			if (choise == countEl - 1) {
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
			cout << "> " << menu[choise];
			SetConsoleTextAttribute(hStdout, 07 | FOREGROUND_INTENSITY);
			cout.flush();
			break;
		}
	}
	SetConsoleTextAttribute(hStdout, 07);
	return choise;
}