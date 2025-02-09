#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

struct Stack {
	string data;
	Stack* tail;
};

struct List {
	string data;
	struct List* head;
};

struct Queue {
	struct List* head, * tail;
};

int choiseMenu(string*, int, int, int);
// сделать функцию замены всех вхождений подстроки в строку
int main(){
	string expression;
	bool usualNot, ReversePolNot, DirectPolNot;
	cout << "Введите выражение (разделяйте числа и операторы пробелами):" << endl;
	getline(cin, expression);
	//expression.replace(1, 3,"46");
}
// рекурсию для решения обычного выражения
// стек для обратной польской нотации
//
int solutionUsualNot(string expression) {
	for (int i = 0; expression[i] != '\0'; i++) {
		// сначала разбить по + и - затем рассматривать выражения
	}
}

bool checkUsualNot(string expression) {
	
	for (int i = 0; expression[i] != '\0'; i++) {

	}
}

bool checkReversePolNot(string expression) {
	// сделать проверку на скобки и дальше на расположение операторов
}

bool checkDirectPolNot(string expression) {

}

int choiseMenu(string* menu, int countEl, int startX, int startY) {
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
