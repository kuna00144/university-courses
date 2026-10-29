#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream inStream;
	ofstream outStream;

	inStream.open("infile.txt");
	if (inStream.fail()) {
		cout << "파일 열기에 실패하였습니다." << endl;
		exit(1);
	}
	outStream.open("outfile.txt");

	const int nSizeMax = 100;
	int nSize = 0, sum = 0;
	int* pnData = new int[nSizeMax];
	while (nSize < nSizeMax && inStream >> pnData[nSize]) {
		sum = sum + pnData[nSize];
		nSize++;
	}
	
	outStream << "20201599 이건아\n" << "파일의 끝 : " << nSize << endl;
	outStream << "infile.txt 파일에서의 sum 값 : " << sum << endl;

	delete[] pnData;
	inStream.close();
	outStream.close();

	return 0;
}