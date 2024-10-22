#include <iostream>
using namespace std;

int main()
{
	const int sizeMat = 10;
	int mat[sizeMat][sizeMat];
	int x = 0, y = 0, c = 0;
	bool flag = true;
	for (int x = 0; x < sizeMat; ++x) {
		if (flag) {
			for (int y = 0; y < sizeMat; ++y) {
				mat[x][y] = c;
				cout << x << "  " << y << '\n';
				++c;
			}
			flag = false;
		}
		else {
			for (int y = 9; y >= 0; +--y) {
				mat[x][y] = c;
				cout << x << "  " << y << '\n';
				++c;
			}
			flag = true;
		}
	}
	for (int i = 0; i < sizeMat; ++i) {
		for (int j = 0; j < sizeMat; ++j) {
			cout << mat[j][i] << " ";
		}
		cout << '\n';
	}


	return 0;
}