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
	CTheater();
	CTheater(string strName, int nTripTime, int pnShowTime[], int nSize);
	void SetName(string strName);
	string GetName();
	void SetTripTime(int nTripTime);
	int GetTripTime();
	void SetShowTime(int pnShowTime[], int nSize);
	void GetShowTime(int pnShowTime[], int nSize);
	void PrintSchedule();
	void InputTheaterInfo(string strName, int nTripTime, int pnShowTime[], int nSize);
};