#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>

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
	int weight;
	AvlTree* p;
	AvlTree* left;
	AvlTree* right;
};

struct RbTree {
	int data;
	char colour;
	RbTree* p;
	RbTree* left;
	RbTree* right;
};

void binTreeInsert(BinTree*&, int);
void printBinTree(BinTree*, int);

template <typename treeType>
int lefttTreeDepth(treeType* tree, int depth = 0) {
	depth++;
	if(tree->left)
}

void PrintTree(BinTree* tree, int posY, int posX) {
	if (tree->left){
		PrintTree(tree->left, posY + 4, posX - 3);
	}
	if (tree->p->left == tree) {
		
	}
	else {
		
	}
	destCoord.Y = posY;
	destCoord.X = posX;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << tree->data;
	cout.flush();

	if (tree->p){
		destCoord.Y = posY - 1;
		destCoord.X = posX;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << 'V';
		cout.flush();

		destCoord.Y = posY - 2;
		destCoord.X = posX;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << '|';
		cout.flush();

		destCoord.Y = posY - 3;
		destCoord.X = posX - 1;
		SetConsoleCursorPosition(hStdout, destCoord);
		if (tree->p->left == tree) {
			destCoord.X = posX + 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << '/';
		}
		else {
			destCoord.X = posX - 1;
			SetConsoleCursorPosition(hStdout, destCoord);
			cout << '\\';
		}
		cout.flush();
	}

	if (tree->right) {
		PrintTree(tree->right, posY + 4, posX + 3);
	}
}

int main(){
	BinTree* tree = NULL;
	binTreeInsert(tree, 1);
	binTreeInsert(tree, 4);
	binTreeInsert(tree, -8);
	binTreeInsert(tree, 2);
	binTreeInsert(tree, 3);
	binTreeInsert(tree, -10);
	binTreeInsert(tree, -9);
	binTreeInsert(tree, 7);
	binTreeInsert(tree, 5);
	binTreeInsert(tree, 30);
	binTreeInsert(tree, 6);
	binTreeInsert(tree, 8);
	PrintTree(tree, 0, 10);
	getchar();
}

void binTreeInsert(BinTree*& root, int newEl) {
	if (root) {
		if (root->data > newEl) {
			if (root->left) {
				binTreeInsert(root->left, newEl);
			}
			else {
				root->left = new BinTree;
				root->left->data = newEl;
				root->left->p = root;
			}
		}
		else {
			if (root->right) {
				binTreeInsert(root->right, newEl);
			}
			else {
				root->right = new BinTree;
				root->right->data = newEl;
				root->right->p = root;
			}
		}
	}
	else {
		root = new BinTree;
		root->data = newEl;
	}
}

void printBinTree(BinTree* root, int posY = 0) {
	int left = 0, right = 0;
	int posX = 5;
	if (root->left) {
		for (BinTree* curr = root->left; curr->left; curr = curr->left) {
			left++;
		}
	}
	posX = left * 5;
	destCoord.Y = posY;
	destCoord.X = posX;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << root->data;
	cout.flush();
	if (root->left){
		destCoord.X = posX - 2;
		destCoord.Y = posY + 1;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << '|';
		destCoord.X = posX - 2;
		destCoord.Y = posY + 2;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << '|';
		destCoord.X = posX - 2;
		destCoord.Y = posY + 3;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << 'V';
		destCoord.X = posX - 2;
		destCoord.Y = posY + 4;
		SetConsoleCursorPosition(hStdout, destCoord);
		getchar();
		printBinTree(root->left, posY + 4);
		cout.flush();
	}
	if (root->right) {
		for (BinTree* curr = root->right; curr->right; curr = curr->right) {
			right++;
		}
		destCoord.X = posX + 2;
		destCoord.Y = posY + 1;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << '|';
		destCoord.X = posX + 2;
		destCoord.Y = posY + 2;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << '|';
		destCoord.X = posX + 2;
		destCoord.Y = posY + 3;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << 'V';
		destCoord.X = posX + 2;
		destCoord.Y = posY + 4;
		SetConsoleCursorPosition(hStdout, destCoord);
		getchar();
		printBinTree(root->right, posY+4);
		cout.flush();
	}
}




void avlTreeInsert(AvlTree*& root, int newEl) {
	if (root) {

	}
	else {
		root = new AvlTree;
		root->data = newEl;
	}
}

void rbTreeInsert(RbTree*& root, int newEl) {
	if (root) {

	}
	else {
		root = new RbTree;
		root->data = newEl;
	}
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
