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

Student createNewstudent(string, char, int, int, int*, int*);

void menu();
void printStudents();
Student* readCSV(int&, string);
bool writeCSV(string);
Student* tableRealloc(Student*, int, int);
void printTable(Student*, int);

int main() {
	setlocale(0, "");
	int rows;
	Student* studentsTable = readCSV(rows, "Студенты.csv");;
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

void menu() {
	int choise = 0;
	int press = 0;
	int x = 0, y = 0;
	string menu[9] = { "Создание новой записи о студенте."
		, "Внесение изменений в уже имеющуюся запись."
		, "Данных о студентах."
		, "Информация обо всех студентах группы N.N – инициализируется пользователем."
		, "Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию."
		, "Количество студентов мужского и женского пола.                                                           "
		, "Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»"
		, "Данные о студентах, имеющих номер в списке – k."
		, "Выход" };
	while (true) {
		cout << "Создание новой записи о студенте.\n"
			<< "Внесение изменений в уже имеющуюся запись.\n"
			<< "Данных о студентах.\n"
			<< "Информация обо всех студентах группы N.N – инициализируется пользователем.\n"
			<< "Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию.\n"
			<< "Количество студентов мужского и женского пола.\n"
			<< "Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»;\n"
			<< "Данные о студентах, имеющих номер в списке – k.\n"
			<< "Выход\n";
		while (_getch() != 0x0D) {
			press = _getch();
			switch (press) {
			case 0x48:
				destCoord.Y = y;
				SetConsoleCursorPosition(hStdout, destCoord);
				SetConsoleTextAttribute(hStdout, 07);
				cout << menu[choise] << "  ";
				cout.flush();
				if (choise == 0) {
					choise = 8;
					y = 8;
				}
				else {
					choise--;
					y--;
				}
				destCoord.Y = y;
				SetConsoleCursorPosition(hStdout, destCoord);
				SetConsoleTextAttribute(hStdout, 240);
				cout << "> " << menu[choise];
				cout.flush();
				break;
			case 0x50:
				destCoord.X = x;
				destCoord.Y = y;
				SetConsoleCursorPosition(hStdout, destCoord);
				SetConsoleTextAttribute(hStdout, 07);
				cout << menu[choise] << "  ";
				cout.flush();
				if (choise == 8) {
					choise = 0;
					y = 0;
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
				cout.flush();
				break;
			}
		}
		SetConsoleTextAttribute(hStdout, 07);

		switch (choise) {
		case 0:
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
		case 8:
			return;
			break;
		}
	}
}

Student createNewstudent(string name, char sex, int group, int number, int gradesDifTest[], int gradesSession[]) {
	struct Student newStudent;
	newStudent.name = name;
	newStudent.sex = sex;
	newStudent.group = group;
	newStudent.number = number;
	for (int i = 0; i < 5; i++) {
		newStudent.gradesDifTest[i] = gradesDifTest[i];
	}
	for (int i = 0; i < 3; i++) {
		newStudent.gradesSession[i] = gradesSession[i];
	}
	return newStudent;
}