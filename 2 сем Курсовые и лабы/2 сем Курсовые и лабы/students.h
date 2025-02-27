#pragma once
#include <string>
using namespace std;

namespace firstPract {

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

	Student* addStudent(string fileName, Student* studentsTable, Student newStudent, int& rows);
	Student* replaceStudent(string fileName, Student* studentsTable, Student newStudent, int& rows, int numberStudent);
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

}