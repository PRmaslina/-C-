#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <chrono>
#include <fstream>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

class Application
{
	int countRows;
	string* rows = {
			"Задать массив",
			"Рассчитать среднее и СКО элентов массива",
			"команду, инициирующую сортировку элементов массива по возрастанию или убыванию",
			"команду, инициирующую изменения размерности массива",
			"команду, инициирующую изменения значения выбранного элемента массива",
			"команду, инициирующую вывод в консоль элементов текущего объекта массива",
			"команду выхода из приложения"
	};

	Application() {
		rows = {
			"Задать массив",
			"Рассчитать среднее и СКО элентов массива",
			"команду, инициирующую сортировку элементов массива по возрастанию или убыванию",
			"команду, инициирующую изменения размерности массива",
			"команду, инициирующую изменения значения выбранного элемента массива",
			"команду, инициирующую вывод в консоль элементов текущего объекта массива",
			"команду выхода из приложения"
		};
	}
};

struct RbTree {
	int data;
	char color = 'b';
	RbTree* p = NULL;
	RbTree* left = NULL;
	RbTree* right = NULL;
};

void printRbTree(RbTree* root, int posX, int posY);
int choiseMenu(string*, int, int, int);

template<typename TreeType>
void leftRotate(TreeType* root) {
	TreeType* y = root->right;
	if (root->p) {
		if (root->p->left == root){
			(root->p->left) = (root->right);
		}
		else {
			root->p->right = root->right;
		}
	}
	y->p = root->p;
	root->p = root->right;
	if (root->right->left) {
		root->right->left->p = root;
	}
	root->right = y->left;
	y->left = root;
}

template<typename TreeType>
void rightRotate(TreeType* root) {
	TreeType* y = root->left;
	if (root->p) {
		if (root->p->left == root) {
			(root->p->left) = (root->left);
		}
		else {
			root->p->right = root->left;
		}
	}
	y->p = root->p;
	root->p = root->left;
	if (root->left->right) {
		root->left->right->p = root;
	}
	root->left = y->right;
	y->right = root;
}

template<typename TreeType>
int numberOfNodes(TreeType* root, int number) {
	if (root) {
		if (root->left) {
			number += 1 + numberOfNodes<TreeType>(root->left, 0);
		}
		if (root->right) {
			number += 1 + numberOfNodes<TreeType>(root->right, 0);
		}
		return number;
	}
	else {
		return number;
	}
}

template<typename TreeType>
TreeType* minNodeTree(TreeType* root) {
	while (root->left) {
		root = root->left;
	}
	return root;
}

template<typename TreeType>
TreeType* findNubmerTree(TreeType* root, int number, string& log) {
	log += " --> ищём число ";
	if (!root) {
		log += " --> такого числа нет";
		return NULL;
	}
	else if(root->data == number){
		log += " --> число найдено, возвращаем значение";
		return root;
	}
	else if (root->data < number) {
		log += " --> идем направо ";
		return findNubmerTree<TreeType>(root->right, number, log);
	}
	else {
		log += " --> идем налево ";
		return findNubmerTree<TreeType>(root->left, number, log);
	}
}

template<typename TreeType>
void transplantNode(TreeType*& root, TreeType*& node1, TreeType*& node2) {
	if (!node1->p) {
		root = node2;
	}
	else if (node1 == node1->p->left) {
		node1->p->left = node2;
	}
	else {
		node1->p->right = node2;
	}
	if (node2) {
		node2->p = node1->p;
	}
}

 int deleteBalanceRb(RbTree*& root, RbTree* node, string& log) {
	RbTree* w;
	auto timeStart1 = chrono::steady_clock::now();
	log += " --> проверям дерево на дисбаланс";
	while (node && node != root && node->color == 'b') {
		log += " --> деревно не сбалансиравано, выполняем балансировку";
		if (node == node->p->left) {
			w = node->p->right;
			if (w->color == 'r') {
				w->color = 'b';
				node->p->color = 'r';
				leftRotate<RbTree>(node->p);
				w = node->p->right;
			}
			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				node = node->p;
			}
			else if (w->right->color == 'b') {
				w->left->color = 'b';
				w->color = 'r';
				rightRotate<RbTree>(w);
				w = node->p->right;
				w->color = node->p->color;
				node->p->color = 'b';
				w->right->color = 'b';
				leftRotate<RbTree>(node->p);
				node = root;
			}
			else {
				w->color = node->p->color;
				node->p->color = 'b';
				w->right->color = 'b';
				leftRotate<RbTree>(node->p);
				node = root;
			}
		}
		else {
			w = node->p->left;
			if (w->color == 'r') {
				w->color = 'b';
				node->p->color = 'r';
				rightRotate<RbTree>(node->p);
				w = node->p->left;
			}
			if (w->right->color == 'b' && w->left->color == 'b') {
				w->color = 'r';
				node = node->p;
			}
			else if (w->left->color == 'b') {
				w->right->color = 'b';
				w->color = 'r';
				leftRotate<RbTree>(w);
				w = node->p->left;
				w->color = node->p->color;
				node->p->color = 'b';
				w->left->color = 'b';
				rightRotate<RbTree>(node->p);
				node = root;
			}
			else {
				w->color = node->p->color;
				node->p->color = 'b';
				w->left->color = 'b';
				rightRotate<RbTree>(node->p);
				node = root;
			}
		}
	}
	if (node){
		log += " --> устанавливаем цвет корня - черным";
		node->color = 'b';
	}
	log += " --> дерево сбалансировано";
	auto timeEnd1 = chrono::steady_clock::now();
	return chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count();
}

int deleteNodeRb(RbTree*& root, RbTree* node, bool timeBalance, string& log) {
	int time = 0;
	auto timeStart = chrono::steady_clock::now();
	if (node == root) {
		delete root;
		root = NULL;
		return 1;
	}
	if (node) {
		RbTree* y = node, * x;
		char origColor = y->color;
		log += " --> наиболее подходящим узлом";
		if (!node->left) {
			x = node->right;
			transplantNode<RbTree>(root, node, node->right);
		}
		else if (!node->right) {
			x = node->left;
			transplantNode<RbTree>(root, node, node->left);
		}
		else {
			y = minNodeTree<RbTree>(node->right);
			origColor = y->color;
			x = y->right;
			if (y->p == node) {
				x->p = y;
			}
			else {
				transplantNode<RbTree>(root, y, y->right);
				y->right = node->right;
				y->right->p = y;
			}
			transplantNode<RbTree>(root, node, y);
			y->left = node->left;
			y->left->p = y;
			y->color = node->color;
		}
		if (origColor == 'b') {
			time = deleteBalanceRb(root, x, log);
		}
		delete node;
	}
	auto timeEnd = chrono::steady_clock::now();
	if (timeBalance) {
		cout << time << " nanosecond: ушло на балансировку после удаления" << endl;
	}
	return chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();
}

template<typename TreeType>
void treeInsert(TreeType*& root, int newEl) {
	if (root) {
		if (root->data > newEl) {
			if (root->left) {
				treeInsert(root->left, newEl);
			}
			else {
				root->left = new TreeType;
				root->left->data = newEl;
				root->left->p = root;
			}
		}
		else {
			if (root->right) {
				treeInsert(root->right, newEl);
			}
			else {
				root->right = new TreeType;
				root->right->data = newEl;
				root->right->p = root;
			}
		}
	}
	else {
		root = new TreeType;
		root->data = newEl;
	}
}

int insertBalanceRb(RbTree*& root, RbTree*& newNode, string& log) {
	RbTree* y;
	auto timeStart1 = chrono::steady_clock::now();
	log += " --> проверям дерево на дисбаланс";
	while (newNode->p->color == 'r') {
		log += " --> деревно не сбалансиравано, выполняем балансировку";
		if (newNode->p == newNode->p->p->left) {
			y = newNode->p->p->right;
			if (y && y->color == 'r') {
				newNode->p->color = 'b';
				y->color = 'b';
				newNode->p->p->color = 'r';
				newNode = newNode->p->p;
			}
			else if (newNode == newNode->p->right) {
				newNode = newNode->p;
				leftRotate<RbTree>(newNode);
				newNode->p->color = 'b';
				newNode->p->p->color = 'r';
				rightRotate<RbTree>(newNode->p->p);
			}
			else {
				newNode->p->color = 'b';
				newNode->p->p->color = 'r';
				rightRotate<RbTree>(newNode->p->p);
			}
		}
		else {
			y = newNode->p->p->left;
			if (y && y->color == 'r') {
				newNode->p->color = 'b';
				y->color = 'b';
				newNode->p->p->color = 'r';
				newNode = newNode->p->p;
			}
			else if (newNode == newNode->p->left) {
				newNode = newNode->p;
				rightRotate<RbTree>(newNode);
				newNode->p->color = 'b';
				newNode->p->p->color = 'r';
				leftRotate<RbTree>(newNode->p->p);
			}
			else {
				newNode->p->color = 'b';
				newNode->p->p->color = 'r';
				leftRotate<RbTree>(newNode->p->p);
			}
		}
		if (!newNode->p) {
			break;
		}
	}
	while (root->p) {
		root = root->p;
	}
	log += " --> устанавливаем цвет корня - черным";
	root->color = 'b';
	log += " --> дерево сбалансировано";
	auto timeEnd1 = chrono::steady_clock::now();
	return chrono::duration_cast<chrono::nanoseconds>(timeEnd1 - timeStart1).count();
}

int rbTreeInsert(RbTree*& root, int newEl, bool timeBalance, string& log) {
	int time;
	auto timeStart = chrono::steady_clock::now();

	bool check = true;
	RbTree* y = NULL, * x = root;
	RbTree* newNode = new RbTree;
	newNode->data = newEl;
	while (x) {
		y = x;
		if (newEl < x->data) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	log += " --> находим предка для нового элемента ";
	newNode->p = y;
	if (!y) {
		root = newNode;
		log += " --> элементов в дереве нет, теперь новый элемент - корень";
		check = false;
	}
	else if (newEl < y->data) {
		y->left = newNode;
		log += " --> устанавливаем новый элемент левым потомком" ;
	}
	else{
		y->right = newNode;
		log += " --> устанавливаем новый элемент правым потомком";
	}
	if(check){
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->color = 'r';
		time = insertBalanceRb(root, newNode, log);
	}
	auto timeEnd = chrono::steady_clock::now();
	if (timeBalance) {
		cout << time << " nanosecond: нужно для балансировки" << endl;
	}
	return chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();
}

int inputRbTree(RbTree*& root, string& log) {
	system("cls");
	string stringArray;
	string logSecond;
	while (root) {
		deleteNodeRb(root, root, false, logSecond);
	}
	cout << "Введите числа через пробел, из них будет формировано дерево" << endl;
	getline(cin, stringArray);
	stringArray += ' ';
	string newInt = "";
	int leadTime = 0;
	for (int i = 0; stringArray[i]; i++) {
		if (isdigit(stringArray[i]) || stringArray[i] == '-') {
			newInt += stringArray[i];
		}
		else if (newInt != "") {
			log += " --> вставляем число " + newInt;
			if(findNubmerTree<RbTree>(root, stoi(newInt), log) == NULL){
				auto timeStart = chrono::steady_clock::now();
				rbTreeInsert(root, stoi(newInt), false, log);
				auto timeEnd = chrono::steady_clock::now();
				leadTime += chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();
			}
			newInt = "";
		}
	}
	return leadTime;
}

int fillRbTree(RbTree*& root) {
	string logSecond;
	while (root) {
		deleteNodeRb(root, root, false, logSecond);
	}
	system("cls");
	string log;
	int N , leadTime = 0;
	cout << "Введите число элементов" << endl;
	cin >> N;
	string newInt = "";
	srand(time(0));
	for (int i = 0, c; i < N; i++) {
		c = rand() % N;
		while (findNubmerTree<RbTree>(root, c, log) != NULL) {
			c = rand() % N;
		};
		auto timeStart = chrono::steady_clock::now();
		rbTreeInsert(root, c, false, log);
		auto timeEnd = chrono::steady_clock::now();
		leadTime += chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();
	}
	return leadTime;
}

int createRbTree(RbTree*& RbRoot) {
	system("cls");
	string log;
	string menu[2] = { "1) Заполнить введенными числами",
						"2) Заполнить случаными числами "};
	cout << "Как заполнить дерево?";
	int choise = choiseMenu(menu, 2, 0, 1);
	int leadTime;
	switch (choise) {
	case 0:
		leadTime = inputRbTree(RbRoot, log);
		break;
	case 1:
		leadTime = fillRbTree(RbRoot);
		break;
	}
	return leadTime;
}

void printRbTree(RbTree* root, int posX, int posY) {
	if (root)
	{
		if (root->right)
		{
			if (root->right->left)
			{
				SetConsoleTextAttribute(hStdout, root->right->color == 'r' ? FOREGROUND_RED : FOREGROUND_GREEN);
				for (int i = 1; i < numberOfNodes(root->right->left, 2); i++) {
					destCoord.X = posX + 4;
					destCoord.Y = posY - i;
					SetConsoleCursorPosition(hStdout, destCoord);
					cout << '|';
					cout.flush();
				}
				printRbTree(root->right, posX + 4, posY - numberOfNodes(root->right->left, 2));
			}
			else
			{
				printRbTree(root->right, posX + 4, posY - 1);
			}
		}
		destCoord.X = posX;
		destCoord.Y = posY;
		SetConsoleCursorPosition(hStdout, destCoord);
		SetConsoleTextAttribute(hStdout, root->color == 'r' ? FOREGROUND_RED : FOREGROUND_GREEN);
		if (root->p)
		{
			if (root->p->left == root)
			{
				cout << "`-->" << root->data << endl;
			}
			else
			{
				cout << ".-->" << root->data << endl;
			}
		}
		else
		{
			cout << "--->" << root->data << endl;
		}
		cout.flush();
		SetConsoleTextAttribute(hStdout, root->color == 'r' ? FOREGROUND_RED : FOREGROUND_GREEN);
		if (root->left)
			if (root->left->right)
			{
				SetConsoleTextAttribute(hStdout, root->left->color == 'r' ? FOREGROUND_RED : FOREGROUND_GREEN);
				for (int i = 1; i < numberOfNodes(root->left->right, 2); i++) {
					destCoord.X = posX + 4;
					destCoord.Y = posY + i;
					SetConsoleCursorPosition(hStdout, destCoord);
					cout << '|';
					cout.flush();
				}
				printRbTree(root->left, posX + 4, posY + numberOfNodes(root->left->right, 2));
			}
			else
			{
				printRbTree(root->left, posX + 4, posY + 1);
			}
	}
}

void generateTasks() {
	string tasks = "1) Сформировать дерево";
	string ansvers = "";
	string keys = "";
	int numberTasks = 1;
	int* tasksArr = new int[1];
	tasksArr[0] = 0;
	RbTree* RbRoot = NULL;
	string menu[4] = { "+ Переформировать дерево",
					   "+ удалить элемент       ",
					   "+ вставить элемент      ",
					   "закончить             " };
	int number, choise = 0;
	while (choise != 3) {
		system("cls");
		cout << tasks;
		choise = choiseMenu(menu, 4, 0, numberTasks + 1);
		system("cls");
		switch (choise) {
		case 0:
			tasksArr = (int*)realloc(tasksArr, (numberTasks + 1) * sizeof(int));
			tasksArr[numberTasks] = 0;
			numberTasks++;
			tasks += '\n' + to_string(numberTasks) + ") Переформировать дерево";
			break;
		case 1:
			tasksArr = (int*)realloc(tasksArr, (numberTasks + 1) * sizeof(int));
			tasksArr[numberTasks] = 1;
			numberTasks++;
			cout << "Введите число которое надо удалить" << endl;
			cin >> number;
			tasks += '\n' + to_string(numberTasks) + ")  удалить элемент " + to_string(number);
			break;
		case 2:
			tasksArr = (int*)realloc(tasksArr, (numberTasks + 1) * sizeof(int));
			tasksArr[numberTasks] = 2;
			numberTasks++;
			cout << "Введите число которое надо вставить" << endl;
			cin >> number;
			tasks += '\n' + to_string(numberTasks) + ")  вставить элемент " + to_string(number);
			break;
		}
	}
	getchar();
	for (int i = 0; i < numberTasks; i++) {
		switch (tasksArr[i]) {
		case 0:
			ansvers += to_string(i + 1) + ") ";
			keys += to_string(i + 1) + ") " + to_string(inputRbTree(RbRoot, ansvers)) + " nanosecond: время создания RB дерева" + '\n';
			ansvers += '\n';
			break;
		case 1:
			ansvers += to_string(i + 1) + ") ";
			keys += to_string(i + 1) + ") " + to_string(deleteNodeRb(RbRoot, findNubmerTree(RbRoot, number, ansvers), false, ansvers)) + " nanosecond: время удаления числа из RB дерева" + '\n';
			ansvers += '\n';
			break;
		case 2:
			ansvers += to_string(i + 1) + ") ";
			keys += to_string(i + 1) + ") " + to_string(rbTreeInsert(RbRoot, number, false, ansvers)) + " nanosecond: время вставки числа в RB дерево" + '\n';
			ansvers += '\n';
			break;
		}
	}
	fstream file;
	file.open("output_task.txt");
	if (file.is_open()) {
		file << tasks;
		file.close();
	}
	file.open("output_key.txt");
	if (file.is_open()) {
		file << keys;
		file.close();
	}
	file.open("output_ans.txt");
	if (file.is_open()) {
		file << ansvers;
		file.close();
	}
}

template <typename TreeType>
int findTime(TreeType* root, int number) {
	string log = "";
	auto timeStart = chrono::steady_clock::now();
	findNubmerTree<TreeType>(root, number, log);
	auto timeEnd = chrono::steady_clock::now();
	return chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	RbTree* RbRoot = NULL;
	string log = "";
	cout << createRbTree(RbRoot) << " nanosecond: время создания RB дерева";
	string menu[8] = {"1) Пересоздать Красно-черное дерево",
					  "2) Вывести Красно-черное дерево     ",
					  "3) удалить элемент                  ",
					  "4) вставить элемент                 ",
					  "5) Время поиска элемент             ",
					  "6) Сгенерировать задания            ",
					  "0) Назад                            "};
	int number, choise = 0;
	while (choise != 6) {
		system("cls");
		choise = choiseMenu(menu, 7, 0, 0);
		system("cls");
		switch (choise) {
			case 0:
				cout << createRbTree(RbRoot) << " nanosecond: время создания RB дерева";
				break;
			case 1:
				printRbTree(RbRoot, 0, RbRoot->right ? numberOfNodes(RbRoot->right, 2) : 2);
				break;
			case 2:
				cout << " Введите число которые хотите удалить " << endl;
				cin >> number;
				cout << deleteNodeRb(RbRoot, findNubmerTree(RbRoot, number, log), true, log) << " nanosecond: время удаления числа из RB дерева";
				break;
			case 3:
				cout << " Введите число которые хотите вставить " << endl;
				cin >> number;
				cout << rbTreeInsert(RbRoot, number, true , log) << " nanosecond: время добавления числа в RB дерево";
				break;
			case 4:
				cout << " Введите число которые хотите найти " << endl;
				cin >> number;
				cout << findTime<RbTree>(RbRoot, number) << " nanosecond: время поиска числа в RB дереве";
				break;
			case 5:
				generateTasks();
				break;
		}
		if (choise < 5) {
			getchar();
			getchar();
		}
	}
}

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