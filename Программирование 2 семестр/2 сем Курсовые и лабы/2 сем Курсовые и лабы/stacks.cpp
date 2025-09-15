#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>

using namespace std;

namespace thirdPract {

	struct Stack {
		int data;
		Stack* tail;
	};

	string DoOperatorUsual(string expression, int place, char typeOper) {
		string number1 = "", number2 = "";
		int leftPlace = place, rightPlace = place;
		for (int j = place - 1, check = 0;j >= 0; j--) {
			if (isdigit(expression[j]) || expression[j] == '-') {
				number1 = expression[j] + number1;
				check = 1;
			}
			else if (check && !isdigit(expression[j])) {
				leftPlace = j + 1;
				break;
			}
		}
		if (number1 == "") {
			number1 = "0";
		}

		for (int j = place + 1, check = 0; j < expression.length(); j++) {
			if (isdigit(expression[j]) || expression[j] == '-') {
				number2 += expression[j];
				check = 1;
			}
			else if (check && !isdigit(expression[j])) {
				rightPlace = j - 1;
				break;
			}
		}

		string equals;
		switch (typeOper) {
		case '*':
			cout << "Умножаем " << number1 << " и " << number2 << ';' << endl;
			equals = to_string(stoi(number1) * stoi(number2));
			break;
		case '/':
			cout << "Делим " << number1 << " и " << number2 << ';' << endl;
			equals = to_string(stoi(number1) / stoi(number2));
			break;
		case '+':
			cout << "Суммируем " << number1 << " и " << number2 << ';' << endl;
			equals = to_string(stoi(number1) + stoi(number2));
			break;
		case '-':
			cout << "Вычитаем " << number1 << " и " << number2 << ';' << endl;
			equals = to_string(stoi(number1) - stoi(number2));
			break;
		}
		while (equals.length() < rightPlace - leftPlace + 1) {
			equals += ' ';
		}
		expression.replace(leftPlace, equals.length(), equals);
		return expression;
	}

	string solutionUsualNot(string expression) {
		string number;
		int count;
		for (int i = 1; expression[i]; i++) {
			if (expression[i] == '(') {
				for (int j = i + 1, check = 1; expression[j]; j++) {
					if (expression[j] == '(') {
						check++;
					}
					else if (expression[j] == ')') {
						check--;
						if (!check) {
							number = solutionUsualNot(expression.substr(i + 1, j - i - 1));
							while (number.length() != j - i + 2) {
								number += ' ';
							}
							expression.replace(i, j - i + 1, number);
							break;
						}
					}
				}
			}
		}
		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '*') {
				expression = DoOperatorUsual(expression, i, '*');
			}
			else if (expression[i] == '/') {
				expression = DoOperatorUsual(expression, i, '/');
			}
		}
		for (int i = 0; i < expression.length(); i++) {
			if (expression[i] == '+') {
				expression = DoOperatorUsual(expression, i, '+');
			}
			else if (expression[i] == '-') {
				expression = DoOperatorUsual(expression, i, '-');
			}
		}
		return expression;
	}

	bool isOperator(char symb) {
		if (symb == '+' || symb == '-' || symb == '*' || symb == '/') {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkUsualNot(string expression) {
		for (int i = 1, firstCheck = 0, secondCheck = 1; expression[i]; i++) {
			if (expression[i] == '(') {
				firstCheck = 1;
				for (int j = i + 1; expression[j]; j++) {
					if (expression[j] == '(') {
						firstCheck++;
					}
					else if (expression[j] == ')') {
						firstCheck--;
						if (!firstCheck) {
							secondCheck += 1;
							break;
						}
					}
				}

			}
			else if (expression[i] == ')') {
				secondCheck--;
				if (!secondCheck) {
					return false;
				}
			}
		}
		for (int i = 1; expression[i]; i++) {
			if (isOperator(expression[i])) {
				if (expression[i] == '-') {
					for (int j = i + 1; !isdigit(expression[j]) && expression[j] != '(' && expression[j] != ')'; j++) {
						if (isOperator(expression[j]) || j == expression.length() - 1) {
							return false;
						}
					}
				}
				else {
					for (int j = i + 1; !isdigit(expression[j]) && expression[j] != '(' && expression[j] != ')'; j++) {
						if ((isOperator(expression[j]) && expression[i] != '-') || (j == expression.length())) {
							return false;
						}
					}
					for (int j = i - 1; !isdigit(expression[j]) && expression[j] != '(' && expression[j] != ')'; j--) {
						if (isOperator(expression[j]) || j == 0) {
							return false;
						}
					}
				}
			}
		}
		for (int i = 1, digitCheck = 0, operatorCheck = 0; expression[i]; i++) {
			if (isdigit(expression[i]) && digitCheck && !operatorCheck) {
				return false;
			}
			else if (isdigit(expression[i]) && digitCheck && operatorCheck) {
				operatorCheck = 0;
				digitCheck = 0;
			}
			else if (isdigit(expression[i]) && !isdigit(expression[i + 1])) {
				digitCheck = 1;
			}
			else if (isOperator(expression[i])) {
				operatorCheck = 1;
			}
		}
		return true;
	}

	void addToStack(Stack*& stack, int number) {
		Stack* last;
		if (stack) {
			last = stack;
			stack = new Stack;
			stack->data = number;
			stack->tail = last;
		}
		else {
			stack = new Stack;
			stack->data = number;
			stack->tail = 0;
		}
	}

	int takeFromStack(Stack*& stack) {
		int data = stack->data;
		Stack* last = stack;
		stack = stack->tail;
		delete last;
		return data;
	}

	int solutionReversePolNot(string expression) {
		string strNumber = "";
		Stack* stack = 0;
		int number1, number2, equals;
		for (int i = 0; expression[i]; i++) {
			if (isdigit(expression[i]) && !isdigit(expression[i + 1])) {
				strNumber += expression[i];
				cout << "Читаем значение " << strNumber << ". Это число. Переносим в стек;" << endl;
				addToStack(stack, stoi(strNumber));
				strNumber = "";
			}
			else if (isdigit(expression[i]) || (isdigit(expression[i + 1]) && expression[i] == '-')) {
				strNumber += expression[i];
			}
			else if (isOperator(expression[i])) {
				cout << "Читаем значение " << expression[i] << ". Это оператор. Забираем числа ";
				number2 = takeFromStack(stack);
				number1 = takeFromStack(stack);
				cout << number1 << " и " << number2 << " из стека.";
				switch (expression[i]) {
				case '*':
					equals = number1 * number2;
					cout << " Умножаем. ";
					break;
				case '/':
					equals = number1 / number2;
					cout << " Делим. ";
					break;
				case '+':
					equals = number1 + number2;
					cout << " Суммируем. ";
					break;
				case '-':
					equals = number1 - number2;
					cout << " Вычитаем. ";
					break;
				}
				cout << equals << " (результат) переносим в стек;" << endl;
				addToStack(stack, equals);
			}
		}
		delete stack;
		cout << "Выражение прочитано. В стеке одно значение = " << equals << ". Это и есть результат вычисления.";
		return equals;
	}

	bool checkReversePolNot(string expression) {
		// сделать проверку на скобки и дальше на расположение операторов
		int checkNumber = 0;
		for (int i = 0; expression[i]; i++) {
			if (expression[i] != ' ' && !isdigit(expression[i]) && !isOperator(expression[i])) {
				return false;
			}
			else if (isdigit(expression[i]) && !isdigit(expression[i + 1])) {
				checkNumber++;
			}
			else if (isOperator(expression[i]) && !(isdigit(expression[i + 1]) && expression[i] == '-')) {
				if (checkNumber < 2) {
					return false;
				}
				checkNumber--;
			}
		}
		return true;
	}

	int solutionDirectPolNot(string expression) {
		string strNumber = "";
		Stack* stack = 0;
		int number1, number2, equals;
		for (int i = expression.length() - 1; i != 0; i--) {
			if (isdigit(expression[i]) || (isdigit(expression[i + 1]) && expression[i] == '-')) {
				strNumber += expression[i];
			}
			else if (!isdigit(expression[i]) && isdigit(expression[i + 1])) {
				strNumber += expression[i];
				cout << "Читаем значение " << strNumber << ". Это - число. Переносим в стек" << endl;
				addToStack(stack, stoi(strNumber));
				strNumber = "";
			}
			else if (isOperator(expression[i])) {
				cout << "Читаем значение " << expression[i] << ". Это - оператор. Забираем числа ";
				number1 = takeFromStack(stack);
				number2 = takeFromStack(stack);
				cout << number1 << " и " << number2 << " из стека. Вычитаем. Результат переносим в стек;" << endl;
				switch (expression[i]) {
				case '*':
					equals = number1 * number2;
					break;
				case '/':
					equals = number1 / number2;
					break;
				case '+':
					equals = number1 + number2;
					break;
				case '-':
					equals = number1 - number2;
					break;
				}
				addToStack(stack, equals);
			}
		}
		delete stack;
		cout << "Выражение прочитано. В стеке - одно значение - " << equals << ". Это и есть результат вычисления.";
		return equals;
	}

	bool checkDirectPolNot(string expression) {
		int checkNumber = 0;
		for (int i = expression.length() - 1; i != 0; i--) {
			if (expression[i] != ' ' && !isdigit(expression[i]) && !isOperator(expression[i])) {
				return false;
			}
			else if (isdigit(expression[i]) && !isdigit(expression[i - 1])) {
				checkNumber++;
				if (expression[i - 1] != '-') {
					i--;
				}
			}
			else if (isOperator(expression[i]) && !(isdigit(expression[i + 1]) && expression[i] == '-')) {
				if (checkNumber < 2) {
					return false;
				}
				checkNumber--;
			}
		}
		return true;
	}

}
