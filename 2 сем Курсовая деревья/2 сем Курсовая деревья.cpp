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
	char colour = 'b';
	RbTree* p = NULL;
	RbTree* left = NULL;
	RbTree* right = NULL;
};

template<typename TreeType>
void leftRotate(TreeType*& root) {
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
	root = y;
}

template<typename TreeType>
void rightRotate(TreeType*& root) {
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
	root = y;
}


void balanceRbTree() {
	
}

void balanceAvlTree() {

}

void fillRbTree() {

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
	while (newNode->p->colour == 'r') {
		if (newNode->p == newNode->p->p->left) {
			y = newNode->p->p->right;
			if (y && y->colour == 'r') {
				newNode->p->colour = 'b';
				y->colour = 'b';
				newNode->p->p->colour = 'r';
				newNode = newNode->p->p;
			}
			else if (newNode == newNode->p->right) {
				newNode = newNode->p;
				leftRotate<RbTree>(newNode);
				newNode->p->colour = 'b';
				newNode->p->p->colour = 'r';
				rightRotate<RbTree>(newNode->p->p);
			}
			else {
				root->colour = 'b';
				return;
			}
		}
		else {
			y = newNode->p->p->left;
			if (y && y->colour == 'r') {
				newNode->p->colour = 'b';
				y->colour = 'b';
				newNode->p->p->colour = 'r';
				newNode = newNode->p->p;
			}
			else if (newNode == newNode->p->left) {
				newNode = newNode->p;
				leftRotate<RbTree>(newNode);
				newNode->p->colour = 'b';
				newNode->p->p->colour = 'r';
				rightRotate<RbTree>(newNode->p->p);
			}
			else {
				root->colour = 'b';
				return;
			}
		}
		if (!newNode->p) {
			break;
		}
	}
	while (root->p != NULL) {
		root = root->p;
	}
	root->colour = 'b';
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
	newNode->colour = 'r';
	insertBalanceRb(root, newNode);
	
}

template<typename TreeType>
int numberOfNodes(TreeType* root, int number) {
	if (root) {
		if(root->left){
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

void printBinTree(BinTree* root, int level){
	if (root)
	{
		printBinTree(root->right, level + 1);
		for (int i = 0; i < level; i++) cout << "    ";
		if(root->p){
			if (root->p->left == root) {
				cout << "`-->" << root->data << endl;
			}
			else {
				cout << ".-->" << root->data << endl;
			}
		}
		else {
			cout << root->data << endl;
		}
		printBinTree(root->left, level + 1);
	}
}

void printRbTree(RbTree* root, int level) {
	if (root)
	{
		printRbTree(root->right, level + 1);
		for (int i = 0; i < level; i++) cout << "    ";
		SetConsoleTextAttribute(hStdout, root->colour == 'r' ? FOREGROUND_RED : FOREGROUND_GREEN);
		if (root->p) {
			if (root->p->left == root) {
				cout << "`-->" << root->data << endl;
			}
			else {
				cout << ".-->" << root->data << endl;
			}
		}
		else {
			cout << root->data << endl;
		}
		SetConsoleTextAttribute(hStdout, root->colour == 'r' ? FOREGROUND_RED : FOREGROUND_GREEN);
		printRbTree(root->left, level + 1);
	}
}

int main(){
	RbTree* root = NULL;
	rbTreeInsert(root, 1);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 4);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, -8);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 2);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 3);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, -10);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, -9);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 7);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 5);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 30);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 6);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 8);
	printRbTree(root, 0);
	system("cls");
	rbTreeInsert(root, 0);
	printRbTree(root, 0);
	system("cls");
	printRbTree(root, 0);
	//cout << numberOfNodes(root, 1);  количество узлов
	getchar();
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
