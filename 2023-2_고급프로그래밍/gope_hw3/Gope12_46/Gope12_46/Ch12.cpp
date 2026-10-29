#include <iostream>
#include <fstream>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	fstream fileStream;
	fileStream.open("infile.txt", ios::out | ios::binary); // 출력 기능
	const int iSize = 1001;
	for (int i = 0; i < iSize; i++) {
		fileStream.write((char*)(&i), sizeof(int));
	}
	fileStream.close();
	fileStream.open("infile.txt", ios::in | ios::out | ios::binary);
	int num;
	ifstream inStream;
	ofstream outStream;

	int nNum;
	cout << "처음 번호 10개는 : ";
	for (int i = 0; i < 10; ++i) {
		fileStream.read((char*)&nNum, sizeof(int));
		cout << nNum << " ";
	}
	cout << endl;

	fileStream.seekp((5 - 1) * sizeof(int));
	int ide = 6;
	fileStream.write((char*)&ide, sizeof(int));

	cout << "2번째부터 4개 읽어서 출력 : ";

	fileStream.seekg((2 - 1) * sizeof(int));
	for (int i = 0; i < 4; i++) {
		fileStream.read((char*)(&nNum), sizeof(int));
		cout << nNum << " ";
	}
	fileStream.close();

	return 0;

}