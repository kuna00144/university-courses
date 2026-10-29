#include <iostream>
#include <string>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	
	string strDays;
	int nDays;
	
	cout << "오늘은 무슨 요일입니까? 세 글자로 입력해 주세요." << endl;
	cin >> strDays;

	if (strDays == "월요일") {
		nDays = 1;
	}
	else if (strDays == "화요일") {
		nDays = 2;
	}
	else if (strDays == "수요일") {
		nDays = 3;
	}
	else if (strDays == "목요일") {
		nDays = 4;
	}
	else if (strDays == "금요일") {
		nDays = 5;
	}
	else if (strDays == "토요일") {
		nDays = 6;
	}
	else if (strDays == "일요일") {
		nDays = 7;
	}

	cout << "오늘은" << nDays << "번째 요일입니다." << endl;

	switch (nDays)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			cout << "주중엔 열심히" << endl;
			break;
		case 6:
		case 7:
			cout << "주말엔 즐겁게" << endl;
			break;
	}
}