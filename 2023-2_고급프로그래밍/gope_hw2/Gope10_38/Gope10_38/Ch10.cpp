	#include <iostream>
using namespace std;

int main() {
	cout << "20201599 ÀÌ°Ç¾Æ" << endl;
	int* p5, **p6;
	int nSize = 3;

	p5 = new int[nSize];
	for (int i = 0; i < nSize; i++) {
		p5[i] = i;
		cout << p5[i] << " ";
	}
	cout << endl;

	int nSizeRow = 3;
	int nSizeCol = 4;
	p6= new int* [nSizeRow];

	for (int i = 0; i < nSizeRow; i++) {
		p6[i] = new int[nSizeCol];
	}

	for (int i = 0; i < nSizeRow; i++) {
		for (int j = 0; j < nSizeCol; j++) {
			cout << "Enter an integer for element (" << i << "," << j << "): ";
			cin >> p6[i][j];
		}
	}

	cout << "Array contents: \n";
	for (int i = 0; i < nSizeRow; i++) {
		for (int j = 0; j < nSizeCol; j++) {
			cout << p6[i][j] << " ";
		}
		cout << "\n";
	}

	for (int i = 0; i < nSizeRow; i++) {
		delete[] p6[i];
	}

	delete[] p6;

	return 0;
}