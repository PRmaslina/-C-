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
void swapList(List*, List*);
bool fillListAndMas(List*, int*, int);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//menu();
	int len;
	cout << "Введите размер массива и списка:" << endl;
	cin >> len;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	List* list = createList(len);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время создания списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	int* arr = new int[len];

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время создания массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	cout << "Нажмите enter чтобы продолжить...";
	getchar();
	getchar();
	menu(list, arr, len);
	//swapList(*list->head, *(*list->head).head);
	//for (List* elem = list; elem->head != 0; elem = elem->head) {
	//	delete elem;
	//}
}

void fillList(List* list, int choise) {
	int count;
	srand(time(0));
	switch (choise) {
	case 0:
		for (List* elem = list; elem->head; elem = elem->head) {
			elem->data = rand();
		}
		break;
	case 1:
		count = 0;
		for (List* elem = list; elem->head; elem = elem->head, count++) {
			elem->data = count;
		}
		break;
	}
}

void fillMas(int* arr, int len, int choise) {
	int count;
	srand(time(0));
	switch (choise) {
	case 0:
		for (int i = 0; i < len; i++) {
			arr[i] = rand();
		}
		break;
	case 1:
		count = 0;
		for (int i = 0; i < len; i++, count++) {
			arr[i] = count;
		}
		break;
	}
}

List* remadeList(List* list, int newLen) {
	List* elem = list;
	for (; elem->head; elem = elem->head) {
		if (elem->tail) {
			delete elem->tail;
		}
	}
	delete elem;
	List* newList = createList(newLen);
	return newList;
}

int* remadeMas(int* arr, int newLen) {
	delete[] arr;
	int* newMas = new int[newLen];
	return newMas;
}

bool deleteIndexElemList(List*& list, int place) {
	int count = 0;
	for (List* elem = list; elem->head; elem = elem->head, count++) {
		if (count == place) {
			if (elem->tail) {
				if (elem->head) {
					elem->head->tail = elem->tail;
					elem->tail->head = elem->head;
				}
				else {
					elem->tail->head = 0;
				}
			}
			else {
				elem->head->tail = 0;
			}
			if (!place) {
				list = elem->head;
			}
			delete elem;
			return true;
		}
	}
	cout << "элемент не найден" << endl;
	return false;
}

int* deleteIndexElemMas(int* arr, int len, int place) {
	int* newMas = new int[len - 1];
	for (int i = 0, j = 0; i < len - 1; i++, j++) {
		if (i == place) {
			j++;
		}
		newMas[i] = arr[j];
	}
	delete[] arr;
	return newMas;
}

bool deleteNumberElemList(List*& list, int number) {
	for (List* elem = list; elem->head; elem = elem->head) {
		if (elem->data == number) {
			if (elem->tail) {
				if (elem->head) {
					elem->head->tail = elem->tail;
					elem->tail->head = elem->head;
				}
				else {
					elem->tail->head = 0;
				}
			}
			else {
				elem->head->tail = 0;
			}
			if (!elem->tail) {
				list = elem->head;
			}
			delete elem;
			return true;
		}
	}
	cout << "элемент не найден" << endl;
	return false;
}

int* deleteNumberElemMas(int* arr, int len, int number) {
	int* newMas = new int[len - 1];
	bool del = false;
	for (int i = 0, j = 0; i < len - 1; i++, j++) {
		if (arr[i] == number && !del) {
			j++;
			del = true;
		}
		newMas[i] = arr[j];
	}
	if (!del) {
		cout << "элемент не найден" << endl;
	}
	delete[] arr;
	return newMas;
}

int binarySearch(int* arr, int number, int start, int end) {
	int rem = 0;
	if ((end - start) / 2 == 0) {
		rem = 1;
	}
	int middleNumb = arr[start + (end - start) / 2 + rem];
	if (middleNumb == number) {
		return start + (end - start) / 2 + rem;
	}
	else if (start + 1 == end || start == end + 1) {
		return -1;
	}
	if (middleNumb > number) {
		end = start + (end - start) / 2 + rem;
		binarySearch(arr, number, start, end);
	}
	else {
		start = start + (end - start) / 2 + rem;
		binarySearch(arr, number, start, end);
	}
}

void insertElemList(List*& list, int place, int number) {
	List* newElem = new List;
	newElem->data = number;
	int count = 0;
	for (List* elem = list; elem->head; elem = elem->head, count++) {
		if (count == place - 1) {
			elem->head->tail = newElem;
			newElem->head = elem->head;
			elem->head = newElem;
			newElem->tail = elem;
			break;
		}
	}
	if (!place) {
		list = newElem;
	}
}

int* insertElemMas(int*& arr, int len, int place, int number) {
	int* newMas = new int[len + 1];
	for (int i = 0, j = 0; i < len + 1; i++, j++) {
		newMas[i] = arr[j];
		if (i == place) {
			newMas[i] = number;
			j--;
		}
	}
	delete[] arr;
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

void swapList(List*& list, List*& elem1, List*& elem2) {
	if (elem1->tail && elem1->tail != elem2) {
		elem1->tail->head = elem2;
	}
	else if (!elem1->tail) {
		list = elem2;
	}
	if (elem1->head && elem1->head != elem2) {
		elem1->head->tail = elem2;
	}
	if (elem2->tail && elem2->tail != elem1) {
		elem2->tail->head = elem1;
	}
	else if (!elem2->tail) {
		list = elem1;
	}
	if (elem2->head && elem2->head != elem1) {
		elem2->head->tail = elem1;
	}
	List* p = elem1->tail, *p2 = elem1->head, *p3 = elem2->tail;
	elem1->head == elem2 ? elem1->tail = elem2: elem1->tail = elem2->tail;
	p == elem2 ? elem1->head = elem2 : elem1->head = elem2->head;
	elem2->head == elem1 ? elem2->tail = elem1 : elem2->tail = p;
	p3 == elem1 ? elem2->head = elem1 : elem2->head = p2;
}

List* findElemList(List* list, int place) {
	int count = 0;
	for (List* elem = list; elem->head; elem = elem->head, count++) {
		if (count == place) {
			return elem;
		}
	}
}

int findIndexElemList(List* list, int number) {
	int count = 0;
	for (List* elem = list; elem->head; elem = elem->head, count++) {
		if (elem->data == number) {
			return count;
		}
	}
}

int findIndexElemMas(int* arr, int len, int number) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == number) {
			return i;
		}
	}
}

bool fillListAndMas(List* list, int* arr, int len) {
	int choise;
	system("cls");
	cout << "Как заполнить:" << endl;
	string menu[2] = { "Случайными числами"
						, "По порядку" };
	choise = choiseMenu(menu, 2, 0, 1);
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	fillList(list, choise);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время заполнения списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	fillMas(arr, len, choise);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время заполнения массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	return choise;
}

int remadeListAndMas(List*& list, int*& arr, int len) {
	system("cls");
	int newLen;
	cout << "Введите новый размер:" << endl;
	cin >> newLen;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	list = remadeList(list, newLen);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время пересоздания списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";
	
	auto timeStart2 = chrono::steady_clock::now();

	arr = remadeMas(arr, newLen);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время пересоздания массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	fillList(list, 1);
	fillMas(arr, newLen,1);
	return newLen;
}

int insertElemListAndMas(List*& list, int*& arr, int len) {
	system("cls");
	int place;
	cout << "Введите номер места вставки:" << endl;
	cin >> place;
	int number;
	cout << "Введите значение нового элемента:" << endl;
	cin >> number;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	insertElemList(list, place, number);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время вставки элемента в список :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	arr = insertElemMas(arr, len, place, number);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время вставки элемента в массив :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	return len + 1;
}

void swapElemListAndMas(List*& list, int* arr, int len) {
	system("cls");
	int place1, place2;
	cout << "Введите номера 1 и 2 элемента:" << endl;
	cin >> place1 >> place2;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	List* elem1 = findElemList(list, place1);
	List* elem2 = findElemList(list, place2);
	swapList(list, elem1, elem2);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время перестановки элементов списка по элементам" << ":  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";
	cout << "Список: ";

	auto timeStart2 = chrono::steady_clock::now();

	elem1 = findElemList(list, place1);
	elem2 = findElemList(list, place2);
	swap(elem1->data, elem2->data);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время перестановки элементов списка по значениям" << ":  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	swap(elem1->data, elem2->data);

	auto timeStart3 = chrono::steady_clock::now();

	swap(arr[place1], arr[place2]);

	auto timeEnd3 = chrono::steady_clock::now();
	cout << "Время перестановки элементов массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd3 - timeStart3).count() << " nanosec\n";
}

void findElemListAndMas(List* list, int* arr, int len) {
	system("cls");
	int place, number;
	cout << "Введите номер элемента:" << endl;
	cin >> place;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	number = findElemList(list, place)->data;

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Его значение " << number << endl;
	cout << "Время получения элемента списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	number = arr[place];

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время получения элемента массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
}

void findNumberListAndMas(List* list, int* arr, int len, bool isSorted) {
	system("cls");
	int place, number;
	cout << "Введите значение элемента:" << endl;
	cin >> number;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	place = findIndexElemList(list, number);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Его номер " << place << endl;
	cout << "Время получения элемента списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	place = isSorted ? binarySearch(arr,number,0,len-1) : findIndexElemMas(arr, len, number);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время получения элемента массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
}

int deleteIndexElemListAndMas(List*& list, int*& arr, int len) {
	system("cls");
	int place;
	int del;
	cout << "Введите номер элемента:" << endl;
	cin >> place;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	del = deleteIndexElemList(list, place);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время удаления элемента списка по индексу :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	arr = deleteIndexElemMas(arr, len, place);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время удаления элемента по индексу :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	return len - del;
}

int deleteNumberElemElemListAndMas(List*& list, int*& arr, int len) {
	system("cls");
	int number;
	bool del;
	cout << "Введите значение элемента:" << endl;
	cin >> number;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	del = deleteNumberElemList(list, number);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время удаления элемента списка по значению :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	arr = deleteNumberElemMas(arr, len, number);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время удаления элемента по значению :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	return len - del;
}

void shakerSortMas(int* arr, int len) {
	bool isChanged = true;
	int start = 0, end = len - 1;
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

void shakerSortList(List* list, int len) {
	bool isChanged = true;
	List *start = list, *end = list;
	for (; end->head; end = end->head);
	while (isChanged == true) {
		isChanged = false;
		for (List* elem = list; elem->head != end; elem = elem->head) {
			if (elem->head->data < elem->data) {
				swap(elem->head->data, elem->data);
				isChanged = true;
			}
		}
		end = end->tail;
		if (!isChanged) {
			break;
		}
		for (List* elem = end; elem->tail != start; elem = elem->tail) {
			if (elem->tail->data > elem->data) {
				swap(elem->tail->data, elem->data);
				isChanged = true;
			}
		}
		start = start->head;
	}
}

void shakerSortListAndMas(List* list, int* arr, int len) {
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	shakerSortList(list, len);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время shakerSort списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	shakerSortMas(arr, len);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время shakerSort массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
}

void quickSortList(List* start, List* end, int s, int e) {
	List* pivot = start;
	int p = s;
	start = start->head;
	s++;
	if (s >= e) {
		return;
	}
	for (List* elem = start; elem->head != end->head; elem = elem->head) {
		if (elem->data < pivot->data) {
			swap(start->data, elem->data);
			start = start->head;
			s++;
		}
	}
	swap(pivot->data, start->tail->data);
	quickSortList(pivot, start->tail,p,s-1);
	quickSortList(start, end,s,e);
}

void quickSortMas(int* arr, int start, int end) {
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
	quickSortMas(arr, pivot, start - 1);
	quickSortMas(arr, start, end);
}

void quickSortListAndMas(List* list, int* arr, int len) {
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	List* end = list;
	for (; end->head; end = end->head);
	quickSortList(list, end, 0, len-1);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время quickSort списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	quickSortMas(arr, 0, len-1);

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время quickSort массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
}

void menu(List* list, int* arr, int len) {
	int choise = 0;
	bool isSorted = fillListAndMas(list, arr, len);
	string menu[11] = { 
	  " 0)  Заполнить заново            "
	, " 1)  Пересоздать                 "
	, " 2)  Вставить новый элемент      "
	, " 3)  Поменять эелементы местами  "
	, "4.1) Удалить элемент по индексу  " 
	, "4.2) Удалить элемент по значению "
	, "5.1) Получить элемент по индексу "
	, "5.2) Получить элемент по значению"
	, "6.1) Отсортировать shakerSort    "
	, "6.2) Отсортировать quickSort     "
	, "-1)  Выход                       " };
	while (choise != 10) {
		cout << "Список: ";
		for (List* elem = list; elem->head; elem = elem->head) {
			cout << elem->data << ' ';
		}
		cout << "\nДинамический массив: ";
		for (int i = 0; i < len; i++) {
			cout << arr[i] << ' ';
		}
		choise = choiseMenu(menu, 11, 0, 8);
		switch (choise){
		case 0:
			isSorted = fillListAndMas(list, arr, len);
			break;
		case 1:
			len = remadeListAndMas(list, arr, len);
			break;
		case 2:
			len = insertElemListAndMas(list, arr, len);
			break;
		case 3:
			swapElemListAndMas(list, arr, len);
			break;
		case 4:
			len = deleteIndexElemListAndMas(list, arr, len);
			break;
		case 5:
			len = deleteNumberElemElemListAndMas(list, arr, len);
			break;
		case 6:
			findElemListAndMas(list, arr, len);
			break;
		case 7:
			findNumberListAndMas(list, arr, len, isSorted);
			break;
		case 8:
			shakerSortListAndMas(list, arr, len);
			break;
		case 9:
			quickSortListAndMas(list, arr, len);
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

