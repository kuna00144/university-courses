#pragma once
#include <iostream>
#include <string> 
using namespace std;
const int nSizeOfShowTime = 10;

class CTheater
{
private:
	string m_strName;
	int m_nTripTime;
	int m_pnShowTime[nSizeOfShowTime];
public:
	void SetName(string strName);
	string GetName();
	void SetTripTime(int nTripTime);
	int GetTripTime();
	void SetShowTime(int pnShowTime[], int nSize);
	void GetShowTime(int pnShowTime[], int nSize); // 배열을 전달받아 직접 클래스 내부의 배열에 복사하기 때문에 반환형이 void로 됨.
	void PrintSchedule();
	void InputTheaterInfo(string strName, int nTripTime, int pnShowTime[], int nSize);
};