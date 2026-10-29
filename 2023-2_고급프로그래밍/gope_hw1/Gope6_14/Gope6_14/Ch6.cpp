#include <iostream>
#include <string>
using namespace std;

// 영화관 structure

struct Theater {
	string strName;  // 영화관 이름
	int nTripTime;   // 영화관 까지 거리
	int pShowTime[10];  // 상영 시간 최대 10개까지 숫자로 1300 이면 13시 00분
};

int main() {
	cout << "20201599 이건아" << endl;

	Theater aTheater = { "메가박스아트나인", 10, {1300, 1600} };

	cout << "학교 근처 영화관은 " << aTheater.strName << "이고, 거리는 " << aTheater.nTripTime << "분이 걸리며" << endl;
	cout << "상영시간은 " << endl;
	
	for (int nindex = 0; nindex < 10; nindex++) {
		int nTime = aTheater.pShowTime[nindex];
		if (nTime == 0) {
			continue;
		}
		cout << nTime << endl;
	}
}