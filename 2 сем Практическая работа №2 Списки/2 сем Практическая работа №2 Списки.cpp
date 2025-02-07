#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <chrono>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

struct List{
	int data;
	List* head;
	List* tail;
};

void menu(List*, int*, int);
int choiseMenu(string*, int, int, int);
List* createList(int);
void swapList(List&, List&);
void fillListAndMas(List*, int*, int);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//menu();
	int len;
	cout << "Введите размер массива и списка:" << endl;
	cin >> len;
	List* list = createList(len);
	int* mas = new int[len];
	fillListAndMas(list, mas, len);

	//swapList(*list->head, *(*list->head).head);
	//for (List* elem = list; elem->head != 0; elem = elem->head) {
	//	delete elem;
	//}
}

void fillListAndMas(List* list, int* mas, int len) {
	int choise;
	int count = 0;
	system("cls");
	string menu[2] = { "Случайными числами"
						, "По порядку" };
	choise = choiseMenu(menu, 2, 0, 0);
	switch (choise) {
	case 0:
		for (List* elem = list; elem->head; elem = elem->head) {
			elem->data = rand();
		}
		for (int i = 0; i < len; i++) {
			mas[i] = rand();
		}
		break;
	case 1:
		count = 0;
		for (List* elem = list; elem->head; elem = elem->head, count++) {
			elem->data = count;
		}
		count = 0;
		for (int i = 0; i < len; i++, count++) {
			mas[i] = count;
		}
		break;
	}
}

List* remadeList(List* list, int len, int newLen) {
	system("cls");
	List* elem = list;
	for (; elem->head != 0; elem = elem->head) {
		if (elem->tail) {
			delete elem->tail;
		}
	}
	delete elem;
	List* list = createList(newLen);
	return list;
}

int* remadeMas(int* mas, int newLen) {
	system("cls");
	delete[] mas;
	int* mas = new int[newLen];
	return mas;
}

void insertElemList(List* list, int place, int number) {
	List* newElem = new List;
	newElem->data = number;
	for (List* elem = list, int count = 0; elem->head; elem = elem->head, count++) {
		if (count == place) {
			elem->head->tail = newElem;
			newElem->head = elem->head;
			elem->head = newElem;
			newElem->tail = elem;
			break;
		}
	}
}

void deleteElemList(List* list, int place) {
	for (List* elem = list, int count = 0; elem->head; elem = elem->head, count++) {
		if (count == place) {
			elem->tail->head = elem->head;
			break;
		}
	}
}

int* insertElemMas(List* list, int* mas, int len, int place, int number) {
	int* newMas = new int[len+1];
	for (int i = 0, j = 0; i < len + 1; i++, j++) {
		newMas[i] = mas[j];
		if (i == place) {
			newMas[i] = number;
			j--;
		}
	}
	delete[] mas;
	return newMas;
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

void swapList(List &el1, List &el2) {
	int el1_data = el1.data;
	el1.data = el2.data;
	el2.data = el1_data;
}

void menu(List* list, int* mas, int len) {
	system("cls");
	cout << "Список: ";
	for (List* elem = list; elem->head; elem = elem->head) {
		cout << elem->data << ' ';
	}
	cout << "\nДинамический массив: ";
	for (int i = 0; i < len; i++) {
		cout << mas[i] << ' ';
	}
	int choise = 0;
	string menu[7] = { "Заполнить заново"
	, "Пересоздать"
	, "Вставить новый элемент"
	, "Удалить элемент"
	, "Поменять эелементы местами" 
	, "Получить элемент"
	, "Выход" };
	while (choise != 6) {
		choise = choiseMenu(menu, 7, 0, 0);
		switch (choise) {
		case 0:
			fillListAndMas(list, mas, len);
			break;
		case 1:
			remadeListAndMas(List * list, int* mas, int len);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		}
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

