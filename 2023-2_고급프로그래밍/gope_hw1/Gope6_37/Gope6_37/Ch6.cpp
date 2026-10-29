#include <iostream>
#include <string>
#include "CTheater.h"
using namespace std;

struct Theater {
	string strName;  // 영화관 이름
	int nTripTime;   // 영화관 까지 거리
	int pShowTime[10];  // 상영 시간 최대 10개까지 숫자로 1300 이면 13시 00분
};

int main() {
	cout << "20201599 이건아" << endl;
	const int nSize = 10;
	int pShowTime[nSize] = { 1300, 1600 };
	CTheater aTheater;
	aTheater.InputTheaterInfo("메가박스아트나인", 10, pShowTime, nSize);

	cout << "학교 근처 영화관은 " << aTheater.GetName() << "이고, 거리는 " << aTheater.GetTripTime() << endl;
	aTheater.PrintSchedule();
}