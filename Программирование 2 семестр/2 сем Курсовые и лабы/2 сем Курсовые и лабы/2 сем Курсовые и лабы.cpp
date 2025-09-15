#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <chrono>

#include "practWorks.h"

using namespace std;

HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

int choiseMenu(string*, int, int, int);
void thirdPractMain();
void secondPractMain();
void menuSecondPract(secondPract::List*, int*, int);
void firstPractMain();
void treesMain();
void firstIDZmenu(string);
firstPract::Student enterStudentData(firstPract::Student*, int, int);
firstPract::Guest enterGuestData(firstPract::Guest*, int, int);
void changeFiles(string&, string&);


void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choise = -1;
	while (choise != 4) {
		system("cls");
		cout << "Выберите работу:";
		string menu[5] = { "1) 1 практическая (Стурктуры)                       "
						 , "2) 2 практическая (Списки)                          "
						 , "3) 3 практическая (Стэки)                           "
						 , "4) Курсовая (Деревья)                               "
						 , "0) Выйти                                            " };
		choise = choiseMenu(menu, 5, 0, 1);
		system("cls");
		switch (choise) {
		case 0:
			firstPractMain();
			break;
		case 1:
			secondPractMain();
			break;
		case 2:
			thirdPractMain();
			break;
		case 3:
			treesMain();
			break;
		}
	}
}


void firstPractMain() {
	int rows;
	string fileStudentsCSV = "Студенты.CSV";
	string fileGuestsCSV = "Гости.CSV";
	firstPract::Student* studentsTable = firstPract::readStudentsCSV(rows, fileStudentsCSV);
	int choise = 0;
	int x = 0, y = 0;
	int inputInt;
	string inputString;
	string menu[11] = {
		  "1) Создать новую запись о студенте                                                                               "
		, "2) Внести изменение в уже имеющуюся запись                                                                       "
		, "3) Вывести список студентов                                                                                      "
		, "4) Вывести информация обо всех студентах группы N                                                                "
		, "5) Вывести топ самых успешных студентов                                                                          "
		, "6) Вывести количество студентов мужского и женского пола                                                         "
		, "7) Вывести данные о студентах, которые не получают стипендию/учатся только на «хорошо» и «отлично»/«отлично»     "
		, "8) Вывести данные о студенте по номеру                                                                           "
		, "9) ИДЗ                                                                                                           "
		, "10) Сменить файлы для чтения и записи                                                                            "
		, "0) Выход                                                                                                         " };
	while (choise != 10) {
		choise = choiseMenu(menu, 11, 0, 1);
		system("cls");
		switch (choise) {
		case 0: // Создание новой записи о студенте
			studentsTable = firstPract::addStudent(fileStudentsCSV, studentsTable, enterStudentData(studentsTable, rows, 0), rows);
			break;
		case 1: // Внесение изменений в уже имеющуюся запись
			firstPract::printStudents(studentsTable, rows);
			cout << "Введите номер студента информацию о котором вы хотите изменить:" << endl;
			do { cin >> inputInt; } while (!(0 < inputInt < rows));

			studentsTable = firstPract::replaceStudent(fileStudentsCSV, studentsTable, enterStudentData(studentsTable, rows, inputInt), rows, inputInt);
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
			cout << "Введите номер нужного студента:" << endl;
			do { cin >> inputInt; } while (!(0 < inputInt < rows));

			firstPract::printInfoStudent(studentsTable, rows, inputInt);
			getchar();
			break;
		case 8: // Меню ИДЗ
			firstIDZmenu(fileGuestsCSV);
			break;
		case 9: // Смена файла
			changeFiles(fileStudentsCSV, fileGuestsCSV);
			break;
		}
		getchar();
		system("cls");
	}
	delete[] studentsTable;
}

void changeFiles(string& fileStudentsCSV, string& fileGuestsCSV) {
	system("cls");
	int choise;
	fstream file;
	cout << "Текущие файлы:" << endl;
	string menu[3] = {"Основной - " + fileStudentsCSV,
					  "ИДЗ - " + fileGuestsCSV,
					  "Назад"};
	string newFile;
	do {
		choise = choiseMenu(menu, 3, 0, 1);
		destCoord.Y = choise + 1;
		switch (choise) {
		case 0:
			destCoord.X = 12;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newFile);
			file.open(newFile);
			if (!file.is_open()) {
				menu[choise] += " введенный файл не открыт";
			}
			else {
				menu[choise] += "Основной - " + newFile;
			}
			fileStudentsCSV = newFile;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "           ";
			break;
		case 1:
			destCoord.X = 7;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newFile);
			file.open(newFile);
			if (!file.is_open()) {
				menu[choise] += " введенный файл не открыт";
			}
			else {
				menu[choise] += "Основной - " + newFile;
			}
			fileGuestsCSV = newFile;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "           ";
			break;
		}
	} while (choise != 2);
}

void firstIDZmenu(string fileGuestsCSV){
	int rows;
	firstPract::Guest* guestsTable = firstPract::readGuestsCSV(rows, fileGuestsCSV);
	int choise = 0;
	int inputInt;
	string inputString;
	string menu[5] = {
		  "1) Создать новую запись о госте                    "
		, "2) Внесение изменений в уже имеющуюся запись       "
		, "3) Вывести список гостей                           "
		, "4) Вывести информацию о гостях                     "
		, "0) Выход                                           " };
	while (choise != 4) {
		choise = choiseMenu(menu, 5, 0, 0);
		system("cls");
		switch (choise) {
		case 0: // Создать новую запись о госте
			guestsTable = firstPract::addGuest(fileGuestsCSV, guestsTable, enterGuestData(guestsTable,rows, 0), rows);
			break;
		case 1: // Внесение изменений в уже имеющуюся запись
			firstPract::printGuests(guestsTable, rows);
			cout << "Введите номер гостя информацию о котором вы хотите изменить:" << endl;
			do { cin >> inputInt; } while (!(0 < inputInt < rows));

			guestsTable = firstPract::replaceGuest(fileGuestsCSV, guestsTable, enterGuestData(guestsTable, rows, inputInt), rows, inputInt);
			break;
		case 2: // Вывести список гостей
			firstPract::printGuests(guestsTable, rows);
			break;
		case 3: // Вывести информацию о гостях
			firstPract::printInfoGuests(guestsTable, rows);
			break;
		}
		getchar();
		system("cls");
	}
}

firstPract::Student enterStudentData(firstPract::Student* studentsTable, int rows, int numberStudent = 0) {
	system("cls");
	int choiseData = 0;
	firstPract::Student newStudent;
	string menu[7];
	if (!numberStudent) {
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
		menu[1] = "Выберите пол М/Ж: " + newStudent.sex;
		menu[2] = "Введите номер группы: " + newStudent.group;
		menu[3] = "Введите оценки за диф зачёты : " + newStudent.gradesDifTest;
		menu[4] = "Введите оценки за сессию : " + newStudent.gradesSession;
		menu[5] = "Заменить    ";
		menu[6] = "Выйти";
	}
	do {
		choiseData = choiseMenu(menu, 7, 0, 0);
		destCoord.Y = choiseData;
		switch (choiseData) {
		case 0:
			destCoord.X = 14;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.name);

			menu[choiseData] = "Введите ФИО : " + newStudent.name;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choiseData] << "           ";
			break;
		case 1:
			destCoord.X = 20;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.sex);

			menu[choiseData] = "Выберите пол М / Ж: " + newStudent.sex;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choiseData] << "                                           ";
			break;
		case 2:
			destCoord.X = 24;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.group);

			menu[choiseData] = "Введите номер группы: " + newStudent.group;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choiseData] << "                                           ";
			break;
		case 3:
			destCoord.X = 33;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesDifTest);

			menu[choiseData] = "Введите оценки за диф зачёты : " + newStudent.gradesDifTest;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choiseData] << "                                           ";
			break;
		case 4:
			destCoord.X = 29;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesSession);

			menu[choiseData] = "Введите оценки за сессию : " + newStudent.gradesSession;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choiseData] << "                                           ";
			break;
		case 5:
			if (firstPract::studentDataCheck(menu, newStudent)) {
				return newStudent;
			}
			break;
		}

	} while (choiseData != 6);

}

firstPract::Guest enterGuestData(firstPract::Guest* guestTable, int rows, int numberGuest = 0) {
	system("cls");
	int choise = 0;
	firstPract::Guest newGuest;
	string menu[7];
	if (!numberGuest) {
		newGuest.number = to_string(rows);
		menu[0] = "Введите ФИО : ";
		menu[1] = "Введите Статус(Выступающий/Слушатель): ";
		menu[2] = "Введите ученую степень: ";
		menu[3] = "Введите университет : ";
		menu[4] = "Введите тему доклада ( \"-\" если слушатель) : ";
		menu[5] = "Добавить     ";
		menu[6] = "Выйти";
	}
	else {
		newGuest = guestTable[numberGuest];
		menu[0] = "Введите ФИО : " + newGuest.name;
		menu[1] = "Введите Статус(Выступающий/Слушатель): " + newGuest.status;
		menu[2] = "Введите ученую степень: " + newGuest.academicDegree;
		menu[3] = "Введите университет : " + newGuest.university;
		menu[4] = "Введите тему доклада ( \"-\" если слушатель) : " + newGuest.theme;
		menu[5] = "Заменить    ";
		menu[6] = "Выйти";
	}
	do {
		choise = choiseMenu(menu, 7, 0, 0);
		destCoord.Y = choise;
		switch (choise) {
		case 0:
			destCoord.X = 16;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newGuest.name);

			menu[choise] = "Введите ФИО : " + newGuest.name;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "           ";
			break;
		case 1:
			destCoord.X = 43;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newGuest.status);

			menu[choise] = "Введите Статус(Выступающий/Слушатель): " + newGuest.status;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 2:
			destCoord.X = 28;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newGuest.academicDegree);

			menu[choise] = "Введите ученую степень: " + newGuest.academicDegree;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 3:
			destCoord.X = 25;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newGuest.university);

			menu[choise] = "Введите университет : " + newGuest.university;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 4:
			destCoord.X = 48;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newGuest.theme);

			menu[choise] = "Введите тему доклада ( \"-\" если слушатель) : " + newGuest.theme;
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 5:
			if (firstPract::guestDataCheck(menu, newGuest)) {
				return newGuest;
			}
			break;
		}

	} while (choise != 6);
}


void secondPractMain() {
	int len;
	cout << "Введите размер массива и списка:" << endl;
	cin >> len;
	system("cls");
	auto timeStart1 = chrono::steady_clock::now();

	secondPract::List* list = secondPract::createList(len);

	auto timeEnd1 = chrono::steady_clock::now();
	cout << "Время создания списка :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count() << " nanosec\n";

	auto timeStart2 = chrono::steady_clock::now();

	int* arr = new int[len];

	auto timeEnd2 = chrono::steady_clock::now();
	cout << "Время создания массива :  " << chrono::duration_cast<chrono::nanoseconds>(timeEnd2 - timeStart2).count() << " nanosec\n";
	cout << "Нажмите enter чтобы продолжить...";
	getchar();
	getchar();
	menuSecondPract(list, arr, len);
}

void menuSecondPract(secondPract::List* list, int* arr, int len) {
	int choise = 0;
	system("cls");
	string fillMenu[2] = { "Случайными числами"
				, "По порядку" };
	cout << "Заполнить:" << endl;
	choise = choiseMenu(fillMenu, 2, 0, 1);
	system("cls");
	bool isSorted = fillListAndMas(list, arr, len, choise);
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
		for (secondPract::List* elem = list; elem->head; elem = elem->head) {
			cout << elem->data << ' ';
		}
		cout << "\nДинамический массив: ";
		for (int i = 0; i < len; i++) {
			cout << arr[i] << ' ';
		}
		choise = choiseMenu(menu, 11, 0, 8);
		switch (choise) {
		case 0:
			system("cls");
			cout << "Заполнить:" << endl;
			choise = choiseMenu(fillMenu, 2, 0, 1);
			system("cls");
			isSorted = secondPract::fillListAndMas(list, arr, len, choise);
			break;
		case 1:
			len = secondPract::remadeListAndMas(list, arr, len);
			break;
		case 2:
			len = secondPract::insertElemListAndMas(list, arr, len);
			break;
		case 3:
			secondPract::swapElemListAndMas(list, arr, len);
			break;
		case 4:
			len = secondPract::deleteIndexElemListAndMas(list, arr, len);
			break;
		case 5:
			len = secondPract::deleteNumberElemElemListAndMas(list, arr, len);
			break;
		case 6:
			secondPract::findElemListAndMas(list, arr, len);
			break;
		case 7:
			secondPract::findNumberListAndMas(list, arr, len, isSorted);
			break;
		case 8:
			isSorted = secondPract::shakerSortListAndMas(list, arr, len);
			break;
		case 9:
			isSorted = secondPract::quickSortListAndMas(list, arr, len);
			break;
		}
	}
}


void thirdPractMain() {
	string expression;
	int choise = -1;
	cout << "Введите выражение (разделяйте числа и операторы пробелами):" << endl;
	getline(cin, expression);
	expression = ' ' + expression + ' ';
	while (choise != 4) {
		system("cls");
		cout << expression << endl;
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


void treesMain() {
	int choise = -1;
	string menu[4] = { "1) RB Дерево                                        "
				      ,"2) AVL Дерево                                       "
					  ,"3) Бинарное дерево поиска                           "
				      ,"0) Назад                                            " };
	while (choise != 3) {
		choise = choiseMenu(menu, 4, 0, 0);
		system("cls");
		switch (choise) {
		case 0:

			break;
		case 1:

			break;
		case 2:

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
