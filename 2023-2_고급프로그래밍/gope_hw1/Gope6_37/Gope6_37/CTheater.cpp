#include "CTheater.h"
void CTheater::SetName(string strName) {  // mutator
	m_strName = strName;
}

string CTheater::GetName() {              // accessor
	return m_strName;
}

void CTheater::SetTripTime(int nTripTime) {  // mutator
	m_nTripTime = nTripTime;
}

// accessor
int CTheater::GetTripTime()
{
	return m_nTripTime;
}

// precondition nSize <= 10
void CTheater::SetShowTime(int pnShowTime[], int nSize) {
	for (int nIndex = 0; nIndex < nSize; nIndex++) {
		m_pnShowTime[nIndex] = pnShowTime[nIndex];
	}
}

// precondition nSize <= 10
void CTheater::GetShowTime(int pnShowTime[], int nSize) {
	for (int nIndex = 0; nIndex < nSize; nIndex++) {
		pnShowTime[nIndex] = m_pnShowTime[nIndex];
	}
}

void CTheater::PrintSchedule() {
	cout << "영화 시간표는 다음과 같습니다." << endl;
	for (int nIndex = 0; nIndex < nSizeOfShowTime; nIndex++) {
		if (m_pnShowTime[nIndex] == 0) {
			continue;
		}
		cout << m_pnShowTime[nIndex] << endl;
	}
}

void CTheater::InputTheaterInfo(string strName, int nTripTime, int pnShowTime[], int nSize) { // CTheater class안에 private에 저장
	m_strName = strName;
	m_nTripTime = nTripTime;
	for (int nIndex = 0; nIndex < nSize; nIndex++) {
		m_pnShowTime[nIndex] = pnShowTime[nIndex];
	}
}
