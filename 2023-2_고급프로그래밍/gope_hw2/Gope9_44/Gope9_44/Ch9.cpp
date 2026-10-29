#include <iostream>
#include <string>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	char chString1[30] = "Hello", chString2[30];
	string strEx, strF;
	int pos = 0;
	string str;
	strEx = "How are you? ";
	strF = "are";

	cout << "are 글자 시작 위치 : " << strEx.find(strF, pos) << endl; // str.find(찾을 단어, 어디부터 찾을지)
	// str.find_first_of(strF, pos)는 a, r, e중에 먼저 나오는 위치를 저장
	strcpy_s(chString1, strEx.c_str());

	cout << chString1 << endl;
}