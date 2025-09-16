#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <chrono>

namespace secondPract {

	using namespace std;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	struct List {
		int data;
		List* head;
		List* tail;
	};

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

	void fillList(List * list, int choise) {
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

	List* remadeList(List * list, int newLen) {
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

	bool deleteIndexElemList(List * &list, int place) {
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

	bool deleteNumberElemList(List * &list, int number) {
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

	void insertElemList(List * &list, int place, int number) {
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

	void swapList(List * &list, List * &elem1, List * &elem2) {
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
		List* p = elem1->tail, * p2 = elem1->head, * p3 = elem2->tail;
		elem1->head == elem2 ? elem1->tail = elem2 : elem1->tail = elem2->tail;
		p == elem2 ? elem1->head = elem2 : elem1->head = elem2->head;
		elem2->head == elem1 ? elem2->tail = elem1 : elem2->tail = p;
		p3 == elem1 ? elem2->head = elem1 : elem2->head = p2;
	}

	List* findElemList(List * list, int place) {
		int count = 0;
		for (List* elem = list; elem->head; elem = elem->head, count++) {
			if (count == place) {
				return elem;
			}
		}
	}

	int findIndexElemList(List * list, int number) {
		int count = 0;
		for (List* elem = list; elem->head; elem = elem->head, count++) {
			if (elem->data == number) {
				return count;
			}
		}
		return -1;
	}

	int findIndexElemMas(int* arr, int len, int number) {
		for (int i = 0; i < len; i++) {
			if (arr[i] == number) {
				return i;
			}
		}
		return -1;
	}

	bool fillListAndMas(List * list, int* arr, int len, int choise) {
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

	int remadeListAndMas(List * &list, int*& arr, int len) {
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
		fillMas(arr, newLen, 1);
		return newLen;
	}

	int insertElemListAndMas(List * &list, int*& arr, int len) {
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

	void swapElemListAndMas(List * &list, int* arr, int len) {
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

	void findElemListAndMas(List * list, int* arr, int len) {
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

	void findNumberListAndMas(List * list, int* arr, int len, bool isSorted) {
		system("cls");
		int place, number;
		cout << "Введите значение элемента:" << endl;
		cin >> number;
		system("cls");
		auto timeStart1 = chrono::steady_clock::now();

		place = findIndexElemList(list, number);

		auto timeEnd1 = chrono::steady_clock::now();
		if (place == -1) {
			cout << "Такого значения нет в массиве" << endl;
		}
		else {
			cout << "Его номер " << place << endl;
		}
		cout << "Время получения элемента списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";
		if (isSorted) {
			cout << "Так как массив отсортирован то можно использовать бинарный поиск" << endl;
		}
		auto timeStart2 = chrono::steady_clock::now();

		place = isSorted ? binarySearch(arr, number, 0, len - 1) : findIndexElemMas(arr, len, number);

		auto timeEnd2 = chrono::steady_clock::now();
		cout << "Время получения элемента массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	}

	int deleteIndexElemListAndMas(List * &list, int*& arr, int len) {
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

	int deleteNumberElemElemListAndMas(List * &list, int*& arr, int len) {
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

	void shakerSortList(List * list, int len) {
		bool isChanged = true;
		List* start = list, * end = list;
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

	bool shakerSortListAndMas(List * list, int* arr, int len) {
		system("cls");
		auto timeStart1 = chrono::steady_clock::now();

		shakerSortList(list, len);

		auto timeEnd1 = chrono::steady_clock::now();
		cout << "Время shakerSort списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

		auto timeStart2 = chrono::steady_clock::now();

		shakerSortMas(arr, len);

		auto timeEnd2 = chrono::steady_clock::now();
		cout << "Время shakerSort массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
		return true;
	}

	void quickSortList(List * start, List * end, int s, int e) {
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
		quickSortList(pivot, start->tail, p, s - 1);
		quickSortList(start, end, s, e);
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

	bool quickSortListAndMas(List * list, int* arr, int len) {
		system("cls");
		auto timeStart1 = chrono::steady_clock::now();

		List* end = list;
		for (; end->head; end = end->head);
		quickSortList(list, end, 0, len - 1);

		auto timeEnd1 = chrono::steady_clock::now();
		cout << "Время quickSort списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

		auto timeStart2 = chrono::steady_clock::now();

		quickSortMas(arr, 0, len - 1);

		auto timeEnd2 = chrono::steady_clock::now();
		cout << "Время quickSort массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
		return true;
	}

}
