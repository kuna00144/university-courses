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

	CTheater aTheater2;
	int pShowTime2[nSize] = { 1200, 2000 };
	aTheater2.InputTheaterInfo("CGV", 20, pShowTime2, nSize);
	cout << "학교 근처 영화관2은 " << aTheater2.GetName() << "이고, 거리는 " << aTheater2.GetTripTime() << endl;
	aTheater2.PrintSchedule();

	CTheater aTheater3;
	int pShowTime3[nSize] = { 1400, 1800 };
	aTheater3.InputTheaterInfo("롯데시네마", 40, pShowTime3, nSize);
	cout << "학교 근처 영화관3은 " << aTheater3.GetName() << "이고, 거리는 " << aTheater3.GetTripTime() << endl;
	aTheater3.PrintSchedule();

	/*CTheater cgv("cgv", 20, pShowTime3, nSize);
	cgv.PrintSchedule();*/
	// 이런식으로 하면 생성자 이용한 거다.

}

/* 7-20
class Theater {
public:
   Theater();
   Theater(string strName, int nTripTime, int* pnShowTime, int nSizeOfArray);
   void InputTheaterInfo();
   void PrintSchedule();
private:
   string m_strName;
   int m_nTripTime;
   int m_pnShowTime[10];
};

int main() {

   int ShowTime[] = {200, 320, 440, 560, 680, 800, 920, 1040, 1160, 1280};
   Theater cgv("CGV", 120, ShowTime, sizeof(ShowTime)/sizeof(*ShowTime));
   Theater megabox("MEGABOX", 120, ShowTime, sizeof(ShowTime) / sizeof(*ShowTime));
   Theater lotte("LOTTE CINEMA", 120, ShowTime, sizeof(ShowTime) / sizeof(*ShowTime));
   cgv.PrintSchedule();
   megabox.PrintSchedule();
   lotte.PrintSchedule();
   cout << "ParkHyunBIn 20201589";
   return 0;
}

void Theater::InputTheaterInfo() { // set함수
   cout << "Enter Movie Name : ";
   cin >> m_strName;
   cout << "Enter Trip time : ";
   cin >> m_nTripTime;
   cout << "Enter ShowTIme : ";
   for (int i = 0; i < 10; i++) {
	  cin >> m_pnShowTime[i];
   }
}

void Theater::PrintSchedule() {
   cout << "Movie name is " << m_strName << endl;
   cout << "TripTime is " << m_nTripTime / 60 << "hour" << m_nTripTime % 60 << "min." << endl;
   for (int i = 0; i < 10; i++) {
	  cout << m_pnShowTime[i] / 60 << ":" << m_pnShowTime[i] % 60 << "   ";
   }
   cout << endl;
}

Theater::Theater(string strName, int nTripTime, int* pnShowTime, int nSizeOfArray) {
   m_strName = strName;
   m_nTripTime = nTripTime;
   for (int i = 0; i < 10; i++) {
	  if (i < nSizeOfArray) {
		 m_pnShowTime[i] = pnShowTime[i];
	  }
	  else {
		 m_pnShowTime[i] = 0;
	  }
   }
}
*/