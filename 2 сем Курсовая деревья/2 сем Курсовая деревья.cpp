#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <queue>
using namespace std;
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD destCoord;

struct BinTree {
	int data = NULL;
	BinTree* p = NULL;
	BinTree* left = NULL;
	BinTree* right = NULL;
};

struct AvlTree {
	int data;
	int weight = 0;
	AvlTree* p;
	AvlTree* left;
	AvlTree* right;
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


void balanceRbTree() {
	
}

void balanceAvlTree() {

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
TreeType* findNubmerTree(TreeType* root, int number) {
	if (!root) {
		return NULL;
	}
	else if(root->data == number){
		return root;
	}
	else if (root->data < number) {
		return findNubmerTree<TreeType>(root->right, number);
	}
	else {
		return findNubmerTree<TreeType>(root->left, number);
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

void deleteBalanceRb(RbTree*& root, RbTree* node) {
	RbTree* w;
	while (node && node != root && node->color == 'b') {
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
			else if (w->right->color = 'b') {
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
			else if (w->left->color = 'b') {
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
		}
		}
	}
	if (node){
		node->color = 'b';
	}
}

void deleteNodeRb(RbTree*& root, RbTree* node) {
	RbTree* y = node, * x;
	char origColor = y->color;
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
		deleteBalanceRb(root, x);
	}
	delete node;
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

void insertBalanceRb(RbTree*& root, RbTree*& newNode) {
	RbTree* y;
	while (newNode->p->color == 'r') {
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
	root->color = 'b';
}

void rbTreeInsert(RbTree*& root, int newEl) {
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
	newNode->p = y;
	if (!y) {
		root = newNode;
		return;
	}
	else if (newEl < y->data) {
		y->left = newNode;
	}
	else{
		y->right = newNode;
	}
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->color = 'r';
	insertBalanceRb(root, newNode);
	
}


RbTree* createRbTree() {
	RbTree* RbRoot;
	cout << "Как запонить дерево?";
	string menu[2] = {"1) Заполнить введенными числами",
					  "2) Заполнить случаными числами "};
	int choise = 0;
	choise = choiseMenu(menu, 8, 0, 1);
	if (choise){
		RbRoot = fillRbTree(RbRoot);
	}
	else{
		RbRoot = inputRbTree(RbRoot);
	}
	return RbRoot;
}

RbTree* inputRbTree(RbTree* root) {
	string stringArray;
	getline(cin, stringArray);
	stringArray += ' ';
	string newInt = "";
	for (int i = 0; stringArray[i]; i++) {
		if (isdigit(stringArray[i]) || stringArray[i] == '-') {
			newInt += stringArray[i];
		}
		else if (newInt != "") {
			rbTreeInsert(root, stoi(newInt));
			newInt = "";
		}
	}
	return root;
}

RbTree* fillRbTree(RbTree* root) {
	int N;
	int c;
	cin >> N;
	string newInt = "";
	srand(time(0));
	for (int i = 0; i < N; i++) {
		c = rand() % N;
		while (findNubmerTree<RbTree>(root, c) != NULL) {
			c = rand() % N;
		};
		rbTreeInsert(root, c);
	}
	return root;
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

void printBinTree(BinTree* root, int posX, int posY) {
	if (root)
	{
		if (root->right)
		{
			if (root->right->left)
			{
				for (int i = 1; i < numberOfNodes(root->right->left, 2); i++) {
					destCoord.X = posX + 4;
					destCoord.Y = posY - i;
					SetConsoleCursorPosition(hStdout, destCoord);
					cout << '|';
					cout.flush();
				}
				printBinTree(root->right, posX + 4, posY - numberOfNodes(root->right->left, 2));
			}
			else
			{
				printBinTree(root->right, posX + 4, posY - 1);
			}
		}
		destCoord.X = posX;
		destCoord.Y = posY;
		SetConsoleCursorPosition(hStdout, destCoord);
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
		if (root->left)
			if (root->left->right)
			{
				for (int i = 1; i < numberOfNodes(root->left->right, 2); i++) {
					destCoord.X = posX + 4;
					destCoord.Y = posY + i;
					SetConsoleCursorPosition(hStdout, destCoord);
					cout << '|';
					cout.flush();
				}
				printBinTree(root->left, posX + 4, posY + numberOfNodes(root->left->right, 2));
			}
			else
			{
				printBinTree(root->left, posX + 4, posY + 1);
			}
	}
}

int main(){
	BinTree* BinRoot = NULL;
	RbTree* RbRoot = NULL;
	string menu[8] = {"1) Cформировать Красно-черное дерево                   ",
					  "2) Вывести Красно-черное дерево                        ",
					  "3) удалить элемент                                     ",
					  "4) вставить элемент                                    ",
					  "5) Найти элемент элемент                               ",
					  "6) Определенить скорость проверки на сбалансированность",
					  "7) Сгенерировать задания                               ",
					  "0) Назад                                               "};
	int number, choise = 0;
	while (choise != 7) {
		choise = choiseMenu(menu, 8, 0, 0);
		switch (choise) {
			case 0:
				RbRoot = createRbTree();
				break;
			case 1:
				printRbTree(RbRoot, 0, RbRoot->right ? numberOfNodes(RbRoot->right, 2) : 2);
				break;
			case 2:
				cin >> number;
				deleteNodeRb(RbRoot, findNubmerTree(RbRoot, number));
				break;
			case 3:
				cin >> number;
				rbTreeInsert(RbRoot, number);
				break;
			case 4:
				cin >> number;
				cout << findNubmerTree(RbRoot, number) ? "такой элемент есть" : "такого элемента нет";
				break;
			case 5:
				cin >> number;
				cout << findNubmerTree(RbRoot, number) ? "такой элемент есть" : "такого элемента нет";
				break;
			case 6:

				break;
		}
	}
	//root = fillRbTree(root);
	//RbTree* f = findNubmerTree(root, 14);
	////deleteNodeRb(root, findNubmerTree(root, 14));
	//printRbTree(root, 0, numberOfNodes(root->right, 2));
	//deleteNodeRb(root, findNubmerTree(root, 14));
	//printRbTree(root, 30, numberOfNodes(root->right, 2));
	//getchar();
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