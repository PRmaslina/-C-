#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

struct Student {
	string number;
	string name;
	string sex;
	string group;
	string gradesDifTest;// 5
	string gradesSession;// 3
};

bool addStudent(string,int);
void menu();
void printStudents();
Student* readCSV(int&, string);
bool writeCSV(string);
Student* tableRealloc(Student*, int, int);
void printTable(Student*, int);
//choiseMenu(string*, int, int = 0, int = 0);
//printStringArr(string*, int, int = 0, int = 0);

int main() {
	setlocale(0, "");
	int rows;
	Student* studentsTable = readCSV(rows, "Студенты.csv");
	//addStudent("dfdsf", 3);
	//printTable(studentsTable, rows);
	menu();
	delete[] studentsTable;
}


Student* tableRealloc(Student* table, int oldSize, int newSize) {
	Student* newTable = new Student[newSize];
	for (int i = 0; i < oldSize && i < newSize; i++) {
		newTable[i].number = table[i].number;
		newTable[i].name = table[i].name;
		newTable[i].sex = table[i].sex;
		newTable[i].group = table[i].group;
		newTable[i].gradesDifTest = table[i].gradesDifTest;
		newTable[i].gradesSession = table[i].gradesSession;
	}
	delete[] table;
	return newTable;
}

void printTable(Student* table, int rows) {
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		cout << setw(5) << table[i].number << " | " << setw(35) << table[i].name << " | " << setw(3) << table[i].sex << " | " << setw(8) << table[i].group << " | " << setw(10) << table[i].gradesDifTest << " | " << setw(6) << table[i].gradesSession << " |" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
	}
	cout << "     " << " | " << "                                   " << " | " << "   " << " | " << "        " << " | " << "          " << " | " << "      " << " |" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
}

Student* readCSV(int& rows, string fileName) {
	fstream file;
	string line;
	Student* table = new Student[1];
	file.open(fileName);
	if (!file.is_open()) {
		cout << "Файл не открыт\n";
	}
	else {
		rows = 0;
		while (getline(file, line)) {
			line += ';';
			for (int end = 0, start = 0, el = 0; end < line.length() + 1; ++end) {
				if (line[end] == ';') {
					switch (el) {
					case 0:
						table[rows].number = line.substr(start, end - start);
						break;
					case 1:
						table[rows].name = line.substr(start, end - start);
						break;
					case 2:
						table[rows].sex = line.substr(start, end - start);
						break;
					case 3:
						table[rows].group = line.substr(start, end - start);
						break;
					case 4:
						table[rows].gradesDifTest = line.substr(start, end - start);
						break;
					case 5:
						table[rows].gradesSession = line.substr(start, end - start);
						break;
					}
					el++;
					start = end + 1;
				}
			}
			table = tableRealloc(table, (1 + rows), (2 + rows));
			rows++;
		}
	}
	table = tableRealloc(table, (2 + rows), (1 + rows));
	return table;
}

int choiseMenu(string* menu, int countEl,int startX = 0,int startY = 0) {
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

void menu() {
	int choise = 0;
	int x = 0, y = 0;
	string menu[9] = { "Создание новой записи о студенте."
		, "Внесение изменений в уже имеющуюся запись."
		, "Данных о студентах."
		, "Информация обо всех студентах группы N.N – инициализируется пользователем."
		, "Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию."
		, "Количество студентов мужского и женского пола."
		, "Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»"
		, "Данные о студентах, имеющих номер в списке – k."
		, "Выход" };
	while (choise != 8) {
		choise = choiseMenu(menu, 9);
		switch (choise) {
		case 0:
			system("cls");
			addStudent("нфы",2);
			system("cls");
			break;
		case 1:
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
	}
}

bool addStudent(string fileName, int rows) {
	fstream file;
	struct Student newStudent ;
	int choise = 0;
	int x = 0, y = 0;
	string menu[7] = { "Введите ФИО : *ФИО*"
	, "Выберите пол М/Ж: _"
	, "Введите номер группы: ____"
	, "Введите оценки за диф зачёты : _ _ _ _ _"
	, "Введите оценки за сессию : _ _ _"
	, "Добавить"
	, "Выйти" };
	do{
		choise = choiseMenu(menu, 7);
		destCoord.Y = y + choise;
		switch (choise) {
		case 0:
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << "Введите ФИО :                                       ";
			destCoord.X = 14;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.name);
			menu[choise] = "Введите ФИО : " + newStudent.name;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "           ";
			break;
		case 1:
			destCoord.X = 20;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.sex);
			if (newStudent.sex.length() != 1 
				|| (newStudent.sex != "М" && newStudent.sex != "Ж")) {
				menu[choise] = "Выберите пол М/Ж: _ Данные не корректны      ";
			}
			else {
				menu[choise] = "Выберите пол М/Ж: " + newStudent.sex;
				destCoord.X = 0;
				SetConsoleCursorPosition(hStdout, destCoord);
				cout << menu[choise] << "                                           ";
			}
			break;
		case 2:
			destCoord.X = 24;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.group);
			if (newStudent.group.length() != 4 
				|| !isdigit(newStudent.group[0]) 
				|| !isdigit(newStudent.group[1]) 
				|| !isdigit(newStudent.group[2]) 
				|| !isdigit(newStudent.group[3])){
				menu[choise] = "Введите номер группы: ____ Данные не корректны      ";
			}
			else {
				menu[choise] = "Введите номер группы: " + newStudent.group;
				destCoord.X = 0;
				SetConsoleCursorPosition(hStdout, destCoord);
				cout << menu[choise] << "                                           ";
			}
			break;
		case 3:
			destCoord.X = 24;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesDifTest);
			if (newStudent.gradesDifTest.length() != 5) {
				menu[choise] =  "Введите оценки за диф зачёты : _ _ _ _ _ Данные не корректны";
			}
			else {
				menu[choise] = "Введите номер группы: " + newStudent.gradesDifTest;
				destCoord.X = 0;
				SetConsoleCursorPosition(hStdout, destCoord);
				cout << menu[choise] << "                                           ";
			}
			break;
		case 4:

			break;
		case 5:

			break;
		}

	} while (choise != 6);














	//cout << "Введите ФИО:" << endl;
	//getline(cin, newStudent.name);
	//cout << endl;

	//cout << "Выберите пол:" << endl;
	//string menuGender[2] = { "Мужской" , "Женский" };
	//choise = choiseMenu(menuGender, 2,0 , 4);
	//switch (choise) {
	//case 0:
	//	newStudent.sex = "М";
	//	break;
	//case 1:
	//	newStudent.sex = "Ж";
	//	break;
	//}
	//cout << endl;

	//cout << "Введите номер группы:" << endl;
	//cin >> newStudent.group;
	//cout << endl;

	//bool check = false;
	//do {
	//	cout << "Введите оценки за диф зачёты через пробел:" << endl;
	//	getline(cin, newStudent.gradesDifTest);
	//	for (int i = 0; i < newStudent.gradesDifTest.length(); i++) {
	//		if (newStudent.gradesDifTest[i] == '2') {
	//			cout << "Студент не может быть добавлен в таблицу так как он должен быть отчислен" << endl;
	//			string menuExpul[2] = { "Изменить данные" , "Выйти" };
	//			choise = choiseMenu(menuExpul, 2, 0, 14);
	//			if (choise == 1) {
	//				choise = -1;
	//			}
	//			check = false;
	//			break;
	//		}
	//		else {
	//			check = true;
	//		}
	//	}
	//	if (choise == -1) {
	//		return false;
	//	}
	//} while (check != true);

	//cout << "Введите оценки за диф зачёты:" << endl;
	//cin >> newStudent.gradesDifTest;

	return true;
}
