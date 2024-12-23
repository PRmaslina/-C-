#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
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
Student* readCSV(string);
bool writeCSV(string);
Student* tableRealloc(Student*, int, int);

int main() {
	setlocale(0, "");
	Student* studentsTable;
	studentsTable = readCSV("Студенты.csv");
	//menu();
	cout << "---------------------------------------------------------" << endl;
	for (int i = 0; i < 3; i++) {
		cout << setw(5) << studentsTable[i].number << " | " << setw(30) << studentsTable[i].name << " | " << setw(3) << studentsTable[i].sex << " | " << setw(8) << studentsTable[i].group << " |" << endl;
		cout << "---------------------------------------------------------" << endl;
	}
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

Student* readCSV(string fileName) {
	fstream file;
	string line;
	Student* table = new Student[1];
	int count = 0;
	file.open(fileName);
	if (!file.is_open()) {
		cout << "Файл не открыт\n";
	}
	else {
		cout << "Файл открыт\n";
		while (getline(file, line)) {
			for (int end = 0, start = 0, el = 0; end < line.length() + 1; ++end) {
				if (line[end] == ';') {
					switch (el) {
					case 0:
						table[count].number = line.substr(start, end - start);
						break;
					case 1:
						table[count].name = line.substr(start, end - start);
						break;
					case 2:
						table[count].sex = line.substr(start, end - start);
						break;
					case 3:
						table[count].group = line.substr(start, end - start);
						break;
					}
					el++;
					start = end + 1;
				}
			}
			table = tableRealloc(table, (1 + count), (2 + count));
			count++;
		}
	}
	return table;
}

void printTable(Student* table) {
	for (Student* i = table; i < table + (sizeof(table) / sizeof(Student)); i++) {
		cout << i -> number << "  |  " << i -> name << "  |  " << i -> sex << "  |  " << i -> group << "  |  ";
	}
}

void menu() {
	int choise = 0;
	while (true) {
		cout << "1.   Создание новой записи о студенте.\n"
			<< "2.   Внесение изменений в уже имеющуюся запись.\n"
			<< "3.   Данных о студентах.\n"
			<< "4.   Информация обо всех студентах группы N.N – инициализируется пользователем.\n"
			<< "5.   Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию.\n"
			<< "6.   Количество студентов мужского и женского пола.\n"
			<< "7.   Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»;\n"
			<< "8.   Данные о студентах, имеющих номер в списке – k.\n"
			<< "0.   Выход\n";
		cin >> choise;
		switch (choise) {
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
			break;
		case 0:
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