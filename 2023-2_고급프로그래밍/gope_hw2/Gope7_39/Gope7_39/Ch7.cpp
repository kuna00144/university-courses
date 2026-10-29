#include <iostream>
#include <string>
#include "CTheater.h"
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	const int nSize = 10;
	int pShowTime[nSize] = { 1300, 1600 };
	CTheater aTheater1;
	aTheater1.InputTheaterInfo("메가박스", 10, pShowTime, nSize);

	cout << "학교 근처 영화관1은 " << aTheater1.GetName() << "이고, 거리는 " << aTheater1.GetTripTime() << endl;
	aTheater1.PrintSchedule();
	CTheater::PrintNumberOfTheater();

	CTheater aTheater2;
	int pShowTime2[nSize] = { 1200, 2000 };
	aTheater2.InputTheaterInfo("CGV", 20, pShowTime2, nSize);
	cout << "학교 근처 영화관2은 " << aTheater2.GetName() << "이고, 거리는 " << aTheater2.GetTripTime() << endl;
	aTheater2.PrintSchedule();
	CTheater::PrintNumberOfTheater();

	CTheater aTheater3;
	int pShowTime3[nSize] = { 1400, 1800 };
	aTheater3.InputTheaterInfo("롯데시네마", 40, pShowTime3, nSize);
	cout << "학교 근처 영화관3은 " << aTheater3.GetName() << "이고, 거리는 " << aTheater3.GetTripTime() << endl;
	aTheater3.PrintSchedule();
	CTheater::PrintNumberOfTheater();

}