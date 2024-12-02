#include <iostream>
using namespace std;

char* inputString(char *string) {
	int count = 0;
	char symbol;
	cin.get(symbol);
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

void replaceStringElements(char* string,const char sourceStr[],int sourceStrlength, const char finalyStr[],int finalyStrlength) {
	int stringlength = lengthStr(string);
	bool flag;
	for (char* i = string; i < string + stringlength + 1 - sourceStrlength; ++i) {
		flag = true;
		for (int k = 0; k < sourceStrlength; k++) {
			if (*(i + k) != sourceStr[k]) {
				flag = false;
				break;
			}
		}
		if (flag){
			if (sourceStrlength != finalyStrlength) {
				char* s = new char[stringlength + 1 - (i - string)];
				for (char* j = (i + sourceStrlength); j - string < stringlength + 1; ++j) {
					*(s + (j - (i + sourceStrlength))) = *j;
				}
				string = (char*)realloc(string, (stringlength - sourceStrlength + finalyStrlength) * sizeof(char));
				for (char* j = (i + finalyStrlength); j - string < stringlength + 1; ++j) {
					*j = *(s + (j - (i + finalyStrlength)));
				}
				delete[] s;
			}
			for (char* j = i; j < i + finalyStrlength; ++j) {
				*j = *(finalyStr + (j - i));
			}
			i--;
		}
	}
	string[lengthStr(string) + 1] = '\0';
}

void checkRegister(char* string) {
	int stringlength = lengthStr(string);
	for (char* i = string; i < (string + stringlength - 1); ++i) {
		if (isalpha(*(i)) && isupper(*(i + 1)) ){
			*(i + 1) = tolower(*(i + 1));
		}
	}
}

int main() {
	char* string = new char[2];
	string = inputString(string);
	cout << string << endl;
	replaceStringElements(string, "  ", 2, " ",1); //
	replaceStringElements(string, ",,", 2, " ", 1);
	replaceStringElements(string, "...", 2, "\n", 1);
	replaceStringElements(string, "..", 2, ".", 1);
	replaceStringElements(string, "\n", 1, "...", 3);
	replaceStringElements(string, "....", 4, "...", 3);
	replaceStringElements(string, "::", 2, ":", 1);
	replaceStringElements(string, "??", 2, "?", 1);
	replaceStringElements(string, "!!", 2, "!", 1);
	replaceStringElements(string, ";;", 2, ";", 1);
	replaceStringElements(string, "--", 2, "-", 1);
	replaceStringElements(string, "((", 2, "(", 1);
	replaceStringElements(string, "))", 2, ")", 1);
	replaceStringElements(string, "\"\"", 2, "\"", 1);
	checkRegister(string);
	cout << string << endl;
	//delete[] string;
}