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
		string number;
		string name;
		string status;
		string academicDegree;
		string university;
		string theme;
	};

	struct ratingStudent {
		int number;
		int averageGradeSession;
	};

	bool guestDataCheck(string* menu, Guest guest);
	void printGuests(Guest* table, int rows);
	void printInfoGuests(Guest* table, int rows);
	Guest* readGuestsCSV(int& rows, string fileName);
	Guest* addGuest(string fileName, Guest* guestTable, Guest newGuest, int& rows);
	Guest* replaceGuest(string fileName, Guest* guestTable, Guest newGuest, int& rows, int numberStudent);
	Student* readStudentsCSV(int&, string);
	bool studentDataCheck(string*, Student);
	Student* addStudent(string fileName, Student* studentsTable, Student newStudent, int& rows);
	Student* replaceStudent(string fileName, Student* studentsTable, Student newStudent, int& rows, int numberStudent);
	void printStudents(Student*, int);
	void printInfoGroup(Student*, int, string);
	void bestStudents(Student*, int);
	void printInfoSexes(Student*, int);
	void grantStudents(Student*, int);
	void printInfoStudent(Student*, int, int);

}

namespace secondPract {

	struct List {
		int data;
		List* head;
		List* tail;
	};

	void fillList(List* list, int choise);
	void fillMas(int* arr, int len, int choise);
	List* remadeList(List* list, int newLen);
	int* remadeMas(int* arr, int newLen);
	bool deleteIndexElemList(List*& list, int place);
	int* deleteIndexElemMas(int* arr, int len, int place);
	bool deleteNumberElemList(List*& list, int number);
	int* deleteNumberElemMas(int* arr, int len, int number);
	int binarySearch(int* arr, int number, int start, int end);
	void insertElemList(List*& list, int place, int number);
	int* insertElemMas(int*& arr, int len, int place, int number);
	List* createList(int len);
	void swapList(List*& list, List*& elem1, List*& elem2);
	List* findElemList(List* list, int place);
	int findIndexElemList(List* list, int number);
	int findIndexElemMas(int* arr, int len, int number);
	bool fillListAndMas(List* list, int* arr, int len, int choise);
	int remadeListAndMas(List*& list, int*& arr, int len);
	int insertElemListAndMas(List*& list, int*& arr, int len);
	void swapElemListAndMas(List*& list, int* arr, int len);
	void findElemListAndMas(List* list, int* arr, int len);
	void findNumberListAndMas(List* list, int* arr, int len, bool isSorted);
	int deleteIndexElemListAndMas(List*& list, int*& arr, int len);
	int deleteNumberElemElemListAndMas(List*& list, int*& arr, int len);
	void shakerSortMas(int* arr, int len);
	void shakerSortList(List* list, int len);
	bool shakerSortListAndMas(List* list, int* arr, int len);
	void quickSortList(List* start, List* end, int s, int e);
	void quickSortMas(int* arr, int start, int end);
	bool quickSortListAndMas(List* list, int* arr, int len);

}

namespace thirdPract {
	string solutionUsualNot(string);
	int solutionReversePolNot(string);
	int solutionDirectPolNot(string);
	bool checkUsualNot(string);
	bool checkReversePolNot(string);
	bool checkDirectPolNot(string);
}
