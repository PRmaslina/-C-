#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <map>
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

char* inputString(char* string) {
	cin.clear();
	int count = 0;
	char symbol;
	cin >> symbol;
	while (symbol != '\n') {
		string[count] = symbol;
		count++;
		string = (char*)realloc(string, (2 + count) * sizeof(char));
		cin.get(symbol);
	}
	string[count] = '\0';
	cout << string << endl;
	return string;
}

int lengthStr(char* string) {
	int count = 0;
	while (string[count]) {
		count++;
	}
	return count;
}

char* replaceStringElements(char* string, const char sourceStr[], int sourceStrlength, const char finalyStr[], int finalyStrlength) {
	int stringlength = lengthStr(string);
	bool flag;
	for (int i = 0; i < stringlength + 1 - sourceStrlength; ++i) {
		flag = true;
		for (int k = 0; k < sourceStrlength; k++) {
			if (string[i + k] != sourceStr[k]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			if (sourceStrlength != finalyStrlength) {
				char* s = new char[stringlength + 1 - i];
				for (char* j = &string[i + sourceStrlength]; *j != '\0'; ++j) {
					*(s + (j - &string[i + sourceStrlength])) = *j;
				}
				s[stringlength - sourceStrlength - i] = '\0';
				string = (char*)realloc(string, (stringlength - sourceStrlength + finalyStrlength) * sizeof(char));
				string[stringlength - sourceStrlength + finalyStrlength] = '\0';
				for (char* j = &string[i + finalyStrlength]; *j != '\0'; ++j) {
					*j = *(s + (j - &string[i + finalyStrlength]));
				}
				delete[] s;
			}
			for (char* j = &string[i]; j < string + i + finalyStrlength; ++j) {
				*j = *(finalyStr + (j - &string[i]));
			}
			stringlength = lengthStr(string);
			i--;
		}
	}
	return string;
}

void checkRegister(char* string) {
	int stringlength = lengthStr(string);
	for (char* i = string; i < (string + stringlength - 1); ++i) {
		if (isalpha(*(i)) && isupper(*(i + 1))) {
			*(i + 1) = tolower(*(i + 1));
		}
	}
}

char* readFile(char* string, char* fileName) {
	ifstream file;
	char symb = ' ';
	int count = 0;
	int lastGcount = -1;
	int g = 0;
	file.open(fileName);
	if (!file.is_open()) {
		cout << "Файл не открыт\0";
		return string;
	}
	else {
		do {
			file.get(symb);
			string = (char*)realloc(string, (3 + count) * sizeof(char));
			string[count] = symb;
			count++;
		} while (file.gcount() != 0);
		count -= 1;
		string = (char*)realloc(string, (3 + count) * sizeof(char));
		string[count] = '\0';
		return string;
	}
}

char* firstWord(char* string) {
	char* newStr = new char[1];
	int lengthString = lengthStr(string), 
		lengthNewString = 1;
	bool checkWord;
	for (int i = 0, count = 1; i < lengthString; i+=count, count = 1) {
		checkWord = false;
		while (isalpha(string[i + count - 1])) {
			if (tolower(string[i + count]) == tolower(string[i])) {
				checkWord = true;
			}
			count++;
		}
		if (checkWord) {
			newStr = (char*)realloc(newStr, (lengthNewString + count) * sizeof(char));
			lengthNewString += count;
			count = 1;
			while (isalpha(string[i + count - 1])) {
				newStr[count - 1] = string[i + count - 1];
				count++;
			}
		}
	}
	newStr[lengthNewString - 2] = '\0';
	return newStr;
}

char* deleteSymb(char* string) {
	system("cls");
	char* newStr = new char[1];
	cout << "Введите набор букв и (или) цифр бeз пробелов\n";
	newStr = inputString(newStr);
	for (int i = 0; newStr[i] != '\0'; i++) {
		const char* symb = &newStr[i];
		string = replaceStringElements(string, symb, 1, "", 0);
	}
	delete[] newStr;
	return string;
}

void findSubstringLinear(char* string, char* substring) {
	int count;
	bool check;
	for (int i = 0; string[i] != '\0'; i++) {
		count = 0;
		for (int j = 0; substring[j] != '\0'; j++) {
			if (substring[j] == string[i + count]) {
				count++;
				check = true;
			}
			else {
				check = false;
				break;
			}
		}
		if (check) {
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED );
			cout << substring;
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			i += count-1;
		}
		else {
			cout << string[i];
		}
	}
}

void findSubstringKMP(char* string, char* substring) {
	int stringLength = lengthStr(string),
		substringLength = lengthStr(substring);
	int* prefArr = new int[substringLength];
	prefArr[0] = 0;
	int last = 0;
	for (int i = 1, j = 0; i < substringLength;) {
		if (substring[i] == substring[j]) {
			prefArr[i] = j + 1;
			i++;
			j++;
		}
		else {
			if (j == 0) {
				prefArr[i] = 0;
				i++;
			}
			else {
				j = prefArr[j - 1];
			}
		}
	}
	for (int i = 0, j = 0; i < stringLength;) {
		if (string[i] == substring[j]) {
			i++;
			j++;
			if (j == substringLength) {
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
				cout << substring;
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				last = i + 1;
			}
		}
		else {
			if (j == 0) {
				i++;
				for (int k = last; k < i; k++) {
					cout << string[k];
				}
				last = i;
			}
			else {
				j = prefArr[j - 1];
				for (int k = last; k < i - prefArr[j]; k++) {
					cout << string[k];
				}
				last = i - prefArr[j];
			}
		}
	}
	delete[] prefArr;
}

void findSubstringBM(char* string, char* substring) {
	int stringLength = lengthStr(string),
		substringLength = lengthStr(substring);
	bool check = false;
	int count = substringLength;
	int last = 0;
	map<char, int> shiftMap;
	for (int i = 1; i < substringLength; ++i) {
		shiftMap[substring[i-1]] = substringLength - i;
	}
	if (!shiftMap.count(string[substringLength - 1])) {
		shiftMap[substring[substringLength - 1]] = substringLength;
	}
	for (int i = substringLength - 1; i < stringLength;) {
		for (int j = i; j > i - substringLength; --j) {
			if (string[j] == substring[substringLength - 1 - (i - j)]) {
				check = true;
			}
			else {
				check = false;
				if (shiftMap.count(string[j])) {
					for (int k = last; k < i - substringLength + shiftMap[string[j]] + 1; k++) {
						cout << string[k];
					}
					last = i - substringLength + shiftMap[string[j]] + 1;
					i += shiftMap[string[j]];
				}
				else {
					for (int k = last; k < i + 1; k++) {
						cout << string[k];
					}
					last = i + 1;
					i += substringLength;
				}
				break;
			}
		}
		if (check) {
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			cout << substring;
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			last = i + 1;
			i += substringLength;
		}
		if (i > stringLength) {
			for (int k = last; string[k] != '\0'; k++) {
				cout << string[k];
			}
		}
	}
}

int main() {
	setlocale(0, "");
	int choise;
	char* string = new char[2];
	bool isInputed = false;
	char fileName[] = "string.txt";
	char* substring = new char[1];
	do{
		if (isInputed) {
			system("cls");
			cout << "Сткрока:\n" << string << endl;
			cout << "Доступные действия:\n"
				<< "1) Ввести новую строку\n"
				<< "2) Отредактировать строку\n"
				<< "3) Вывести на экран только те слова последовательности, в которых первая буква слова встречается в этом слове еще раз\n"
				<< "4) Вывести на экран ту же последовательность, удалив из всех слов заданный набор букв и (или) цифр\n"
				<< "5) Найти подстроку\n"
				<< "-1) Назад\n";
			do {
				cin >> choise;
				switch (choise) {
				case 1:
					system("cls");
					cout << "Способ ввода строки:\n"
						<< "1) вручную\n"
						<< "2) через файл\n";
					do {
						cin >> choise;
						switch (choise) {
						case 1:
							string = inputString(string);
							break;
						case 2:
							string = readFile(string, fileName);
							break;
						}
					} while (!(choise == 1 || choise == 2));
					break;
				case 2:
					string = replaceStringElements(string, "  ", 2, " ", 1);
					string = replaceStringElements(string, ",,", 2, ",", 1);
					string = replaceStringElements(string, "....", 4, "...", 3);
					string = replaceStringElements(string, "...", 3, "\n", 1);
					string = replaceStringElements(string, "..", 2, ".", 1);
					string = replaceStringElements(string, "\n", 1, "...", 3);
					string = replaceStringElements(string, "::", 2, ":", 1);
					string = replaceStringElements(string, "??", 2, "?", 1);
					string = replaceStringElements(string, "!!", 2, "!", 1);
					string = replaceStringElements(string, ";;", 2, ";", 1);
					string = replaceStringElements(string, "--", 2, "-", 1);
					string = replaceStringElements(string, "((", 2, "(", 1);
					string = replaceStringElements(string, "))", 2, ")", 1);
					string = replaceStringElements(string, "\"\"", 2, "\"", 1);
					checkRegister(string);
					break;
				case 3:
					cout << firstWord(string) << endl;
					break;
				case 4:
					string = deleteSymb(string);
					break;
				case 5:
					system("cls");
					cout << "Введите подстроку:\n";
					substring = inputString(substring);
					system("cls");
					do {
						cout << "Подстрока: " << substring << endl
							<< "Выберите способ поиска  подстроки:\n"
							<< "1) Линейный поиск\n"
							<< "2) Алгоритм Кнута-Мориса-Прата\n"
							<< "3) Алгоритм Боера-Мура\n"
							<< "4) Через Хэш табилицу\n"
							<< "0) Назад\n";
							cin >> choise;
							switch (choise) {
							case 1:
								system("cls");
								findSubstringLinear(string, substring);
								cout << endl;
								break;
							case 2:
								system("cls");
								findSubstringKMP(string, substring);
								cout << endl;
								break;
							case 3:
								system("cls");
								findSubstringBM(string, substring);
								cout << endl;
								break;
							case 4:

								break;
							}
					} while (choise != 0);
					break;
				}
			} while (choise == -1);
		}
		else {
			cout << "Способ ввода строки:\n"
				<< "1) вручную\n"
				<< "2) через файл\n";
			isInputed = true;
			do {
				cin >> choise;
				switch (choise) {
				case 1:
					string = inputString(string);
					break;
				case 2:
					string = readFile(string, fileName);
					break;
				}
			} while (!(choise == 1 || choise == 2));
		}
	} while (choise != -1);

	//delete[] string;
}