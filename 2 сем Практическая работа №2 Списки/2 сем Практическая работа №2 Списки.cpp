#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

struct List{
	int data;
	List* head;
	List* tail;
};

void menu();
int choiseMenu(string*, int, int, int);
List* createList(int);
void swapList(List, List);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//menu();
	int count = 0;
	List* list = createList(3);
	int* mas = new int[3];
	int count = 0;
	for (List* elem = list; elem->head != 0; elem = elem->head,count++) {
		elem->data = count;
	}
	for (List* elem = list; elem->head != 0; elem = elem->head) {
		cout << elem->data << endl;
	}
	swapList(*list->head, *(*list->head).head);
	for (List* elem = list; elem->head != 0; elem = elem->head) {
		cout << elem->data << endl;
	}
	//for (List* elem = list; elem->head != 0; elem = elem->head) {
	//	delete elem;
	//}
}

List* createList(int len) {
	List* curr = 0, * next = 0;
	for (int i = 0; i <= len; i++) {
		curr = new List;
		curr->head = next;
		if (next) {
			next->tail = curr;
		}
		next = curr;
	}
	curr->tail = 0;
	return curr;
}

void swapList(List el1, List el2) {
	int el1_data = el1.data;
	el1.data = el2.data;
	el2.data = el1_data;
}

void menu() {
	int choise = 0;
	string menu[1] = {"Сформировать двусвязный список и динамический массив размерности N"};
	while (choise != 8) {
		choise = choiseMenu(menu, 9, 0, 0);
	}
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

