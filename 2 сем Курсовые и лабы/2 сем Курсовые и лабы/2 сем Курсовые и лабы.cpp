#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <chrono>

#include "stacks.h"
#include "students.h"

using namespace std;

HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

int choiseMenu(string*, int, int, int);
void thirdPract();

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choise = -1;
	while (choise != 4) {
		system("cls");
		string menu[5] = { "1) 1 практическая (Стурктуры)                       "
						 , "2) 2 практическая (Списки)                          "
						 , "3) 3 практическая (Стэки)                           "
						 , "4) Курсовая (Деревья)                               "
						 , "0) Выйти                                            " };
		choise = choiseMenu(menu, 5, 0, 1);
		system("cls");
		switch (choise) {
		case 0:

			break;
		case 1:
			
			break;
		case 2:
			thirdPract();
			break;
		case 3:

			break;
		}
	}
}

void thirdPract() {
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
						 ,"0) Назад                                            " };
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

void firstPract() {
	int rows;
	firstPract::Student* studentsTable = firstPract::readCSV(rows, "Студенты.CSV");
	int choise = 0;
	int x = 0, y = 0;
	int inputInt;
	string inputString;
	string menu[9] = {
		  "Создание новой записи о студенте                                                                                    "
		, "Внесение изменений в уже имеющуюся запись                                                                           "
		, "Данные о студентах                                                                                                  "
		, "Информация обо всех студентах группы N                                                                              "
		, "Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию                             "
		, "Количество студентов мужского и женского пола                                                                       "
		, "Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»"
		, "Данные о студенте, имеющем номер в списке – k.                                                                      "
		, "Выход                                                                                                               " };
	while (choise != 8) {
		choise = choiseMenu(menu, 9, 0, 0);
		system("cls");
		switch (choise) {
		case 0: // Создание новой записи о студенте
			studentsTable = firstPract::addStudent("Студенты.CSV", studentsTable, enterStudentData(rows));
			break;
		case 1: // Внесение изменений в уже имеющуюся запись
			printStudents(studentsTable, rows);
			cout << "Введите номер студента информацию о котором вы хотите изменить:\n";
			cin >> inputInt;
			studentsTable = firstPract::replaceStudent("Студенты.CSV", studentsTable, enterStudentData(rows, inputInt), inputInt);
			break;
		case 2: // Данные о студентах
			firstPract::printStudents(studentsTable, rows);
			break;
		case 3: //Информация обо всех студентах группы N
			cout << "Введите номер группы информацию о которой вы хотите вывести:\n";
			cin >> inputString;
			system("cls");
			firstPract::printInfoGroup(studentsTable, rows, inputString);
			getchar();
			break;
		case 4: // Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию
			firstPract::bestStudents(studentsTable, rows);
			break;
		case 5: // Количество студентов мужского и женского пола
			firstPract::printInfoSexes(studentsTable, rows);
			break;
		case 6: // Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»
			firstPract::grantStudents(studentsTable, rows);
			break;
		case 7: // Данные о студенте, имеющем номер в списке – k.
			do {
				cout << "Введите номер нужного студента:" << endl;
				cin >> inputInt;
				system("cls");
			} while (!(0 < inputInt < rows));
			firstPract::printInfoStudent(studentsTable, rows, inputInt);
			getchar();
			break;

			}
			getchar();
			system("cls");
		}
	delete[] studentsTable;
}

firstPract::Student enterStudentData(int& rows, int numberStudent = 0) {
	system("cls");
	int choise = 0;
	firstPract::Student newStudent;
	string menu[7];
	if (!numberStudent) {firstPract::Student
		newStudent.number = to_string(rows);
		menu[0] = "Введите ФИО : *ФИО*";
		menu[1] = "Выберите пол М/Ж: _";
		menu[2] = "Введите номер группы: ____";
		menu[3] = "Введите оценки за диф зачёты : _____";
		menu[4] = "Введите оценки за сессию : ___";
		menu[5] = "Добавить     ";
		menu[6] = "Выйти";
	}
	else {
		newStudent = studentsTable[numberStudent];
		menu[0] = "Введите ФИО : " + newStudent.name;
		check[0] = true;
		menu[1] = "Выберите пол М/Ж: " + newStudent.sex;
		check[1] = true;
		menu[2] = "Введите номер группы: " + newStudent.group;
		check[2] = true;
		menu[3] = "Введите оценки за диф зачёты : " + newStudent.gradesDifTest;
		check[3] = true;
		menu[4] = "Введите оценки за сессию : " + newStudent.gradesSession;
		check[4] = true;
		menu[5] = "Заменить    ";
		menu[6] = "Выйти";
	}
	do {
		choise = choiseMenu(menu, 7, 0, 0);
		destCoord.Y = y + choise;
		switch (choise) {
		case 0:
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
			cout << menu[choise] << "                                           ";
			break;
		case 2:
			destCoord.X = 24;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.group);

			menu[choise] = "Введите номер группы: " + newStudent.group;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 3:
			destCoord.X = 33;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesDifTest);

			menu[choise] = "Введите оценки за диф зачёты : " + newStudent.gradesDifTest;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 4:
			destCoord.X = 29;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesSession);

			menu[choise] = "Введите оценки за сессию : " + newStudent.gradesSession;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 5:
			if (StudentDataCheck(menu,newStudent)) {
				return newStudent;
			}
			break;
		}

	} while (choise != 6);
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