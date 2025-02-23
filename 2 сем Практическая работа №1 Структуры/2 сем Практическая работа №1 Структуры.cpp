#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

struct Student {
	string number;
	string name;
	string sex;
	string group;
	string gradesDifTest;// 5 6
	string gradesSession;// 3
};

struct Guest {
	string name = "ФИО";
	string status = "Слушатель";
	string academicDegree = "Студент";
	string university = "ЛЭТИ";
	string theme = " - ";
};

struct ratingStudent {
	int number;
	int averageGradeSession;
};

Student* addStudent(string, Student*, int&, int);
void menu(Student*, int&);
void printStudents(Student*, int);
Student* tableRealloc(Student*, int, int);
Student* readCSV(int&, string);
Student CSVtoStructStudent(string);
int choiseMenu(string*, int, int, int);
void printInfoGroup(Student*, int, string);
void bestStudents(Student*, int);
void printInfoSexes(Student*, int);
void grantStudents(Student*, int);
void printInfoStudent(Student*, int, int);

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

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int rows;
	Student* studentsTable = readCSV(rows, "Студенты.CSV");
	menu(studentsTable, rows);
	delete[] studentsTable;
}

Student* readCSV(int& rows, string fileName) {
	ifstream file;
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
			table[rows] = CSVtoStructStudent(line);
			table = tableRealloc(table, (1 + rows), (2 + rows));
			rows++;
		}
	}
	return table;
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

void menu(Student* studentsTable, int& rows) {
	int choise = 0;
	int x = 0, y = 0;
	int inputInt;
	string inputString;
	string menu[9] = {
		"Создание новой записи о студенте"
		, "Внесение изменений в уже имеющуюся запись"
		, "Данные о студентах"
		, "Информация обо всех студентах группы N"
		, "Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию"
		, "Количество студентов мужского и женского пола"
		, "Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»"
		, "Данные о студенте, имеющем номер в списке – k."
		, "Выход" };
	while (choise != 8) {
		choise = choiseMenu(menu, 9, 0, 0);
		switch (choise) {
		case 0: // Создание новой записи о студенте
			system("cls");
			studentsTable = addStudent("Студенты.CSV", studentsTable, rows, 0);
			system("cls");
			break;
		case 1: // Внесение изменений в уже имеющуюся запись
			system("cls");
			printStudents(studentsTable, rows);
			cout << "Введите номер студента информацию о котором вы хотите изменить:\n";
			cin >> inputInt;
			system("cls");
			studentsTable = addStudent("Студенты.CSV", studentsTable, rows, inputInt);
			system("cls");
			break;
		case 2: // Данные о студентах
			system("cls");
			printStudents(studentsTable, rows);
			getchar();
			system("cls");
			break;
		case 3: //Информация обо всех студентах группы N
			system("cls");
			cout << "Введите номер группы информацию о которой вы хотите вывести:\n";
			cin >> inputString;
			system("cls");
			printInfoGroup(studentsTable, rows, inputString);
			getchar();
			getchar();
			system("cls");
			break;
		case 4: // Топ самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию
			system("cls");
			bestStudents(studentsTable, rows);
			getchar();
			system("cls");
			break;
		case 5: // Количество студентов мужского и женского пола
			system("cls");
			printInfoSexes(studentsTable, rows);
			getchar();
			system("cls");
			break;
		case 6: // Данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»
			system("cls");
			grantStudents(studentsTable, rows);
			getchar();
			system("cls");
			break;
		case 7: // Данные о студенте, имеющем номер в списке – k.
			system("cls");
			do {
				cout << "Введите номер нужного студента:" << endl;
				cin >> inputInt;
				system("cls");
			} while (!(0 < inputInt < rows));
			printInfoStudent(studentsTable, rows , inputInt);
			getchar();
			getchar();
			system("cls");
			break;

		}
	}
}

void printStudents(Student* table, int rows) {
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		cout << setw(5) << table[i].number << " | " << setw(35) << table[i].name << " | " << setw(3) << table[i].sex << " | " << setw(8) << table[i].group << " | " << setw(10) << table[i].gradesDifTest << " | " << setw(6) << table[i].gradesSession << " |" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
	}
}

void printGuests(Student* table, int rows) {
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		cout << setw(5) << table[i].number << " | " << setw(35) << table[i].name << " | " << setw(3) << table[i].sex << " | " << setw(8) << table[i].group << " | " << setw(10) << table[i].gradesDifTest << " | " << setw(6) << table[i].gradesSession << " |" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
	}
}

Student* addStudent(string fileName, Student* studentsTable, int& rows, int numberStudent) {
	fstream file;
	struct Student newStudent;
	int choise = 0;
	bool check[5] = { false, false, false, false, false };
	int x = 0, y = 0;
	bool digitCheck = false;
	bool gradeCheck = false;
	string menu[7];
	if (!numberStudent){
		newStudent.number = to_string(rows);
		menu[0] = "Введите ФИО : *ФИО*";
		menu[1] = "Выберите пол М/Ж: _";
		menu[2] = "Введите номер группы: ____";
		menu[3] = "Введите оценки за диф зачёты : _____";
		menu[4] = "Введите оценки за сессию : ___";
		menu[5] = "Добавить     ";
		menu[6] = "Выйти" ;
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
	do{
		choise = choiseMenu(menu, 7, 0, 0);
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
			check[0] = true;
			break;
		case 1:
			destCoord.X = 20;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.sex);
			if (newStudent.sex != "М" && newStudent.sex != "Ж") {
				menu[choise] = "Выберите пол М/Ж: _ Данные не корректны      ";
				check[1] = false;
			}
			else {
				menu[choise] = "Выберите пол М/Ж: " + newStudent.sex;
				destCoord.X = 0;
				SetConsoleCursorPosition(hStdout, destCoord);
				cout << menu[choise] << "                                           ";
				check[1] = true;
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
				check[2] = false;
			}
			else {
				menu[choise] = "Введите номер группы: " + newStudent.group;
				destCoord.X = 0;
				SetConsoleCursorPosition(hStdout, destCoord);
				cout << menu[choise] << "                                           ";
				check[2] = true;
			}
			break;
		case 3:
			destCoord.X = 33;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesDifTest);
			//digitCheck = false;
			gradeCheck = false;
			if (newStudent.gradesDifTest.length() != 5 || 
				!isdigit(newStudent.gradesDifTest[0]) || 
				!isdigit(newStudent.gradesDifTest[1]) || 
				!isdigit(newStudent.gradesDifTest[2]) ||
				!isdigit(newStudent.gradesDifTest[3]) ||
				!isdigit(newStudent.gradesDifTest[4])) {
				menu[choise] =  "Введите оценки за диф зачёты : _____ Данные не корректны                ";
				check[3] = false;
			}
			else {
				for (int i = 0; i < 5; i++) {
					if (int(newStudent.gradesDifTest[i] - '0') < 3) {
						gradeCheck = false;
						menu[choise] = "Введите оценки за диф зачёты : _____ Данный студент должен быть отчислен";
						check[3] = false;
						break;
					}
					else if (int(newStudent.gradesDifTest[i] - '0') > 5) {
						gradeCheck = false;
						menu[choise] = "Введите оценки за диф зачёты : _____ Данные не корректны                ";
						check[3] = false;
						break;
					}
					gradeCheck = true;
				}
				if (gradeCheck) {
					menu[choise] = "Введите оценки за диф зачёты : " + newStudent.gradesDifTest;
					check[3] = true;
				}
			}
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 4:
			destCoord.X = 29;
			SetConsoleCursorPosition(hStdout, destCoord);
			getline(cin, newStudent.gradesSession);
			if (newStudent.gradesSession.length() != 3 ||
				!isdigit(newStudent.gradesSession[0]) ||
				!isdigit(newStudent.gradesSession[1]) ||
				!isdigit(newStudent.gradesSession[2])) {
				menu[choise] = "Введите оценки за сессию : ___ Данные не корректны                ";
				check[4] = false;
			}
			else {
				for (int i = 0; i < 3; i++) {
					if (int(newStudent.gradesSession[i] - '0') < 3) {
						gradeCheck = false;
						menu[choise] = "Введите оценки за сессию : ___ Данный студент должен быть отчислен";
						check[4] = false;
						break;
					}
					else if(int(newStudent.gradesSession[i] - '0') > 5){
						gradeCheck = false;
						menu[choise] = "Введите оценки за сессию : ___ Данные не корректны                ";
						check[4] = false;
						break;
					}
					gradeCheck = true;
				}
				if (gradeCheck) {
					menu[choise] = "Введите оценки за сессию : " + newStudent.gradesSession;
					check[4] = true;
				}
			}
			destCoord.X = 0;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << menu[choise] << "                                           ";
			break;
		case 5:
			if (check[0] && check[1] && check[2] && check[3] && check[4]) {
				file.open(fileName); //std::ios::app
				if (!file.is_open()) {
					menu[choise] += "файл не открыт";
					cout << menu[choise] << "                                           ";
				}
				else {
					if (!numberStudent) {
						studentsTable[rows] = newStudent;
						studentsTable = tableRealloc(studentsTable, (1 + rows), (2 + rows));
						rows++;
					}
					else {
						studentsTable[numberStudent] = newStudent;
					}
					for (int line = 0; line <= rows; line++) {
						file << studentsTable[line].number << ';' << studentsTable[line].name << ';' << studentsTable[line].sex << ';' << studentsTable[line].group << ';' << studentsTable[line].gradesDifTest << ';' << studentsTable[line].gradesSession << endl;
					}
				}
			}
			break;
		}

	} while (choise != 6);
	return studentsTable;
}

Student CSVtoStructStudent(string line) {
	Student newStudent;
	int sepPlaces[6];
	for (int place = 0, sepNum = 0; place < line.length() + 1; ++place) {
		if (line[place] == ';') {
			sepPlaces[sepNum] = place;
			sepNum++;
		}
	}
	newStudent.number = line.substr(0, sepPlaces[0]);
	newStudent.name = line.substr(sepPlaces[0] + 1, sepPlaces[1] - sepPlaces[0] - 1);
	newStudent.sex = line.substr(sepPlaces[1] + 1, sepPlaces[2] - sepPlaces[1] - 1);
	newStudent.group = line.substr(sepPlaces[2] + 1, sepPlaces[3] - sepPlaces[2] - 1);
	newStudent.gradesDifTest = line.substr(sepPlaces[3] + 1, sepPlaces[4] - sepPlaces[3] - 1);
	newStudent.gradesSession = line.substr(sepPlaces[4] + 1, sepPlaces[5] - sepPlaces[4] - 1);
	return newStudent;
}

void printInfoGroup(Student* studentsTable, int rows, string group) {
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		if (studentsTable[i].group == group) {
			cout << setw(5) << studentsTable[i].number << " | " << setw(35) << studentsTable[i].name << " | " << setw(3) << studentsTable[i].sex << " | " << setw(8) << studentsTable[i].group << " | " << setw(10) << studentsTable[i].gradesDifTest << " | " << setw(6) << studentsTable[i].gradesSession << " |" << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
		}
	}
}

void bestStudents(Student* studentsTable, int rows) {
	ratingStudent *rating = new ratingStudent[rows - 1];
	for (int i = 1; i < rows ; i++) {
		rating[i - 1].number = stoi(studentsTable[i].number);
		rating[i - 1].averageGradeSession = int(studentsTable[i].gradesSession[0] + studentsTable[i].gradesSession[1] + studentsTable[i].gradesSession[2] - '0' * 3);
	}

	int stepCount;
	for (int i = 1; i < rows - 1; i++) {
		stepCount = 0;
		while (i - stepCount != 0 && rating[i - stepCount].averageGradeSession > rating[i - 1 - stepCount].averageGradeSession) {
			swap(rating[i - stepCount], rating[i - 1 - stepCount]);
			stepCount++;
		}
	}
	cout << "Топ студентов по среднему баллу за сессию:" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	cout << "Место | Номер |                                 ФИО | Пол |   Группа | диф зачеты | сессия |" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows - 1; i++) {
		cout  << setw(5) << i + 1 << " | " << setw(5) << rating[i].number << " | " << setw(35) << studentsTable[rating[i].number].name << " | " << setw(3) << studentsTable[rating[i].number].sex << " | " << setw(8) << studentsTable[rating[i].number].group << " | " << setw(10) << studentsTable[rating[i].number].gradesDifTest << " | " << setw(6) << studentsTable[rating[i].number].gradesSession << " |" << endl;
		cout << "--------------------------------------------------------------------------------------------" << endl;
	}
}

void printInfoSexes(Student* studentsTable, int rows) {
	int maleCount = 0, femaleCount = 0;
	for (int i = 1; i < rows; i++) {
		studentsTable[i].sex == "М" ? maleCount++: femaleCount++;
	}
	cout << "Студенов мужского пола:  " << maleCount << endl;
	cout << "Студнтов жеского пола:  " << femaleCount << endl;
}

void grantStudents(Student* studentsTable, int rows) {
	bool checkGrades = true;
	cout << "Данные о студентах обучающихся только на «отлично»" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		if (studentsTable[i].gradesDifTest[0] + studentsTable[i].gradesDifTest[1] + studentsTable[i].gradesDifTest[2] + studentsTable[i].gradesDifTest[3] + studentsTable[i].gradesDifTest[4] + studentsTable[i].gradesSession[0] + studentsTable[i].gradesSession[1] + studentsTable[i].gradesSession[2] == '5' * 8) {
			cout << setw(5) << studentsTable[i].number << " | " << setw(35) << studentsTable[i].name << " | " << setw(3) << studentsTable[i].sex << " | " << setw(8) << studentsTable[i].group << " | " << setw(10) << studentsTable[i].gradesDifTest << " | " << setw(6) << studentsTable[i].gradesSession << " |" << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
		}
	}
	cout << endl << "Данные о студентах обучающихся только на на «хорошо» и «отлично»" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		checkGrades = true;
		for (int j = 0; j < 5; j++) {
			if (studentsTable[i].gradesDifTest[j] < '4') {
				checkGrades = false;
				break;
			}
		}
		for (int j = 0; j < 3; j++) {
			if (checkGrades && studentsTable[i].gradesSession[j] < '4') {
				checkGrades = false;
				break;
			}
		}
		if (checkGrades && !(studentsTable[i].gradesDifTest[0] + studentsTable[i].gradesDifTest[1] + studentsTable[i].gradesDifTest[2] + studentsTable[i].gradesDifTest[3] + studentsTable[i].gradesDifTest[4] + studentsTable[i].gradesSession[0] + studentsTable[i].gradesSession[1] + studentsTable[i].gradesSession[2] == '5' * 8)) {
			cout << setw(5) << studentsTable[i].number << " | " << setw(35) << studentsTable[i].name << " | " << setw(3) << studentsTable[i].sex << " | " << setw(8) << studentsTable[i].group << " | " << setw(10) << studentsTable[i].gradesDifTest << " | " << setw(6) << studentsTable[i].gradesSession << " |" << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
		}
	}
	cout << endl << "Данные о студентах которые не получают стипендию" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++) {
		checkGrades = false;
		for (int j = 0; j < 5; j++) {
			if (studentsTable[i].gradesDifTest[j] == '3') {
				checkGrades = true;
				break;
			}
		}
		for (int j = 0; j < 3; j++) {
			if (!checkGrades && studentsTable[i].gradesSession[j] == '3') {
				checkGrades = true;
				break;
			}
		}
		if (checkGrades) {
			cout << setw(5) << studentsTable[i].number << " | " << setw(35) << studentsTable[i].name << " | " << setw(3) << studentsTable[i].sex << " | " << setw(8) << studentsTable[i].group << " | " << setw(10) << studentsTable[i].gradesDifTest << " | " << setw(6) << studentsTable[i].gradesSession << " |" << endl;
			cout << "------------------------------------------------------------------------------------" << endl;
		}
	}
}

void printInfoStudent(Student* studentsTable, int rows , int numberStudent) {
	cout << "Пол : " << studentsTable[numberStudent].sex << endl;
	cout << "ФИО : " << studentsTable[numberStudent].name << endl;
	cout << "Группа : " << studentsTable[numberStudent].group << endl;
	cout << "Оценки за диф зачеты : " << studentsTable[numberStudent].gradesDifTest << endl;
	cout << "Оценки за сессию : " << studentsTable[numberStudent].gradesSession << endl;
}
