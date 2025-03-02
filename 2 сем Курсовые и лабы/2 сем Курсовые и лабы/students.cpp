#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <conio.h>

namespace firstPract {

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;

	using namespace std;

	struct Student {
		string number;
		string name;
		string sex;
		string group;
		string gradesDifTest;// 5 6
		string gradesSession;// 3
	};

	struct Guest {
		string number;
		string name = "ФИО";
		string status = "Слушатель";
		string academicDegree = "Студент";
		string university = "СПБГЭТУ \"ЛЭТИ\"";
		string theme = " - ";
	};

	struct ratingStudent {
		int number;
		int averageGradeSession;
	};

	template<typename Structure>
	Structure* tableRealloc(Structure* table, int oldSize, int newSize) {
		Structure* newTable = new Structure[newSize];
		for (int i = 0; i < oldSize && i < newSize; i++) {
			newTable[i] = table[i];
		}
		return newTable;
	}

	void printStudent(Student student) {
		cout << setw(5) << student.number << " | " << setw(35) << student.name << " | " << setw(3) << student.sex << " | " << setw(8) << student.group << " | " << setw(10) << student.gradesDifTest << " | " << setw(6) << student.gradesSession << " |" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
	}

	void printStudents(Student* table, int rows) {
		cout << "------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			printStudent(table[i]);
		}
	}

	Student* addStudent(string fileName, Student* studentsTable, Student newStudent, int& rows) {
		fstream file;
		file.open(fileName); //std::ios::app
		if (!file.is_open()) {
			cout << " файл не открыт ";
		}
		else {
			studentsTable[rows] = newStudent;
			studentsTable = tableRealloc<Student>(studentsTable, (1 + rows), (2 + rows));
			rows++;
			for (int line = 0; line <= rows; line++) {
				file << studentsTable[line].number << ';' << studentsTable[line].name << ';' << studentsTable[line].sex << ';' << studentsTable[line].group << ';' << studentsTable[line].gradesDifTest << ';' << studentsTable[line].gradesSession << endl;
			}
			return studentsTable;
		}
	}

	Student* replaceStudent(string fileName, Student* studentsTable, Student newStudent, int& rows, int numberStudent) {
		fstream file;
		file.open(fileName); //std::ios::app
		if (!file.is_open()) {
			cout << " файл не открыт ";
		}
		else {
			studentsTable[numberStudent] = newStudent;
			for (int line = 0; line <= rows; line++) {
				file << studentsTable[line].number << ';' << studentsTable[line].name << ';' << studentsTable[line].sex << ';' << studentsTable[line].group << ';' << studentsTable[line].gradesDifTest << ';' << studentsTable[line].gradesSession << endl;
			}
			return studentsTable;
		}
	}

	bool studentDataCheck(string* menu, Student student){
		int choise = 0;
		bool check[5] = { false, false, false, false, false };
		bool digitCheck = false;
		bool gradeCheck = false;
		if (student.name != "") {
			check[0] = true;
		}
		else {
			menu[0] += " Данные не корректны      ";
		}

		if (student.sex != "М" && student.sex != "Ж") {
			menu[1] += " Данные не корректны      ";
			check[1] = false;
		}
		else {
			check[1] = true;
		}

		if (student.group.length() != 4
			|| !isdigit(student.group[0])
			|| !isdigit(student.group[1])
			|| !isdigit(student.group[2])
			|| !isdigit(student.group[3])) {
			menu[2] += " Данные не корректны      ";
			check[2] = false;
		}
		else {
			check[2] = true;
		}
		
		gradeCheck = false;
		if (student.gradesDifTest.length() != 5 ||
			!isdigit(student.gradesDifTest[0]) ||
			!isdigit(student.gradesDifTest[1]) ||
			!isdigit(student.gradesDifTest[2]) ||
			!isdigit(student.gradesDifTest[3]) ||
			!isdigit(student.gradesDifTest[4])) {
			menu[3] += " Данные не корректны                ";
			check[3] = false;
		}
		else {
			for (int i = 0; i < 5; i++) {
				if (int(student.gradesDifTest[i] - '0') < 3) {
					gradeCheck = false;
					menu[3] += " Данный студент должен быть отчислен";
					check[3] = false;
					break;
				}
				else if (int(student.gradesDifTest[i] - '0') > 5) {
					gradeCheck = false;
					menu[3] += " Данные не корректны                ";
					check[3] = false;
					break;
				}
				gradeCheck = true;
			}
			if (gradeCheck) {
				check[3] = true;
			}
		}

		if (student.gradesSession.length() != 3 ||
			!isdigit(student.gradesSession[0]) ||
			!isdigit(student.gradesSession[1]) ||
			!isdigit(student.gradesSession[2])) {
			menu[4] += " Данные не корректны                ";
			check[4] = false;
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (int(student.gradesSession[i] - '0') < 3) {
					gradeCheck = false;
					menu[4] += " Данный студент должен быть отчислен";
					check[4] = false;
					break;
				}
				else if (int(student.gradesSession[i] - '0') > 5) {
					gradeCheck = false;
					menu[4] += " Данные не корректны                ";
					check[4] = false;
					break;
				}
				gradeCheck = true;
			}
			if (gradeCheck) {
				check[4] = true;
			}
		}
		if (check[0] && check[1] && check[2] && check[3] && check[4]) {
			return true;
		}
		else {
			return false;
		}
	}

	Student CSVtoStructStudent(string line) {
		Student newStudent;
		int sepPlaces[6];
		for (int place = 0, sepNum = 0; line[place]; ++place) {
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

	Guest CSVtoStructGuest(string line) {
		Guest newGuest;
		int sepPlaces[6];
		for (int place = 0, sepNum = 0; line[place]; ++place) {
			if (line[place] == ';') {
				sepPlaces[sepNum] = place;
				sepNum++;
			}
		}
		newGuest.number = line.substr(0, sepPlaces[0]);
		newGuest.name = line.substr(sepPlaces[0] + 1, sepPlaces[1] - sepPlaces[0] - 1);
		newGuest.status = line.substr(sepPlaces[1] + 1, sepPlaces[2] - sepPlaces[1] - 1);
		newGuest.academicDegree = line.substr(sepPlaces[2] + 1, sepPlaces[3] - sepPlaces[2] - 1);
		newGuest.university = line.substr(sepPlaces[3] + 1, sepPlaces[4] - sepPlaces[3] - 1);
		newGuest.theme = line.substr(sepPlaces[4] + 1, sepPlaces[5] - sepPlaces[4] - 1);
		return newGuest;
	}

	Guest* addGuest(string fileName, Guest* guestTable, Guest newGuest, int& rows) {
		fstream file;
		file.open(fileName);
		if (!file.is_open()) {
			cout << " файл не открыт ";
		}
		else {
			guestTable[rows] = newGuest;
			guestTable = tableRealloc<Guest>(guestTable, (1 + rows), (2 + rows));
			rows++;
			for (int line = 0; line <= rows; line++) {
				file << guestTable[line].number << ';' << guestTable[line].name << ';' << guestTable[line].status << ';' << guestTable[line].academicDegree << ';' << guestTable[line].university << ';' << guestTable[line].theme << endl;
			}
			return guestTable;
		}
	}

	Guest* replaceGuest(string fileName, Guest* guestTable, Guest newGuest, int& rows, int numberStudent) {
		fstream file;
		file.open(fileName);
		if (!file.is_open()) {
			cout << " файл не открыт ";
		}
		else {
			guestTable[numberStudent] = newGuest;
			for (int line = 0; line <= rows; line++) {
				file << guestTable[line].number << ';' << guestTable[line].name << ';' << guestTable[line].status << ';' << guestTable[line].academicDegree << ';' << guestTable[line].university << ';' << guestTable[line].theme << endl;
			}
			return guestTable;
		}
	}

	void printGuest(Guest guest) {
		cout << setw(5) << guest.number << " | " << setw(35) << guest.name << " | " << setw(13) << guest.status << " | " << setw(30) << guest.academicDegree << " | " << setw(25) << guest.university << " | " << setw(35) << guest.theme << " |" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}

	void printInfoGuests(Guest* table, int rows) {
		cout << "Выступающие:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			if (table[i].status == "Выступающий") {
				printGuest(table[i]);
			}
		}
		cout << endl << "Приглашенные:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			if (table[i].university != "ЛЭТИ") {
				printGuest(table[i]);
			}
		}
		cout << endl << "Выступающие студенты:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			if (table[i].status == "Выступающий" && table[i].academicDegree == "Студент") {
				printGuest(table[i]);
			}
		}
		cout << endl << "Студенты ЛЭТИ:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			if (table[i].university == "СПБГЭТУ \"ЛЭТИ\"" && table[i].academicDegree == "Студент") {
				printGuest(table[i]);
			}
		}
	}

	void printGuests(Guest* table, int rows) {
		cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			printGuest(table[i]);
		}
	}

	bool guestDataCheck(string* menu, Guest guest){
		int choise = 0;
		bool check[5] = { false, false, false, false, false };
		if (guest.name.length() > 2) {
			check[0] = true;
		}
		else {
			menu[0] += " Данные не корректны      ";
		}

		if (guest.status != "Выступающий" && guest.status != "Слушатель") {
			menu[1] += " Данные не корректны      ";
		}
		else {
			check[1] = true;
		}

		if (guest.academicDegree.length() < 2) {
			menu[2] += " Данные не корректны      ";
		}
		else {
			check[2] = true;
		}

		if (guest.university.length() < 1) {
			menu[3] += " Данные не корректны                ";
		}
		else {
			check[3] = true;
		}

		if ((guest.status == "Слушатель" && guest.theme[0] != '-') || (guest.status == "Выступающий" && guest.theme[0] == '-')) {
			menu[4] += " Данные не корректны                ";
		}
		else {
			check[4] = true;
		}

		if (check[0] && check[1] && check[2] && check[3] && check[4]) {
			return true;
		}
		else {
			return false;
		}
	}

	void printInfoGroup(Student* studentsTable, int rows, string group) {
		cout << "------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			if (studentsTable[i].group == group) {
				printStudent(studentsTable[i]);
			}
		}
	}

	void bestStudents(Student* studentsTable, int rows) {
		ratingStudent* rating = new ratingStudent[rows - 1];
		for (int i = 1; i < rows; i++) {
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
			cout << setw(5) << i + 1 << " | " << setw(5) << rating[i].number << " | " << setw(35) << studentsTable[rating[i].number].name << " | " << setw(3) << studentsTable[rating[i].number].sex << " | " << setw(8) << studentsTable[rating[i].number].group << " | " << setw(10) << studentsTable[rating[i].number].gradesDifTest << " | " << setw(6) << studentsTable[rating[i].number].gradesSession << " |" << endl;
			cout << "--------------------------------------------------------------------------------------------" << endl;
		}
	}

	void printInfoSexes(Student* studentsTable, int rows) {
		int maleCount = 0, femaleCount = 0;
		for (int i = 1; i < rows; i++) {
			studentsTable[i].sex == "М" ? maleCount++ : femaleCount++;
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
				printStudent(studentsTable[i]);
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
				printStudent(studentsTable[i]);
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
				printStudent(studentsTable[i]);
			}
		}
	}

	void printInfoStudent(Student* studentsTable, int rows, int numberStudent) {
		cout << "Пол : " << studentsTable[numberStudent].sex << endl;
		cout << "ФИО : " << studentsTable[numberStudent].name << endl;
		cout << "Группа : " << studentsTable[numberStudent].group << endl;
		cout << "Оценки за диф зачеты : " << studentsTable[numberStudent].gradesDifTest << endl;
		cout << "Оценки за сессию : " << studentsTable[numberStudent].gradesSession << endl;
	}

	Student* readStudentsCSV(int& rows, string fileName) {
		ifstream file;
		string line;
		Student* table = new Student;
		file.open(fileName);
		if (!file.is_open()) {
			cout << "Файл не открыт\n";
		}
		else {
			rows = 0;
			while (getline(file, line)) {
				line += ';';
				table[rows] = CSVtoStructStudent(line);
				table = tableRealloc<Student>(table, (1 + rows), (2 + rows));
				rows++;
			}
		}
		return table;
	}

	Guest* readGuestsCSV(int& rows, string fileName) {
		ifstream file;
		string line;
		Guest* table = new Guest;
		file.open(fileName);
		if (!file.is_open()) {
			cout << "Файл не открыт\n";
		}
		else {
			rows = 0;
			while (getline(file, line)) {
				line += ';';
				table[rows] = CSVtoStructGuest(line);
				table = tableRealloc<Guest>(table, (1 + rows), (2 + rows));
				rows++;
			}
		}
		return table;
	}

}
