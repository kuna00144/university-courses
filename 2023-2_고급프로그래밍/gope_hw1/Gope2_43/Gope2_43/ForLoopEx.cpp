#include <iostream>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;

	int pWaiting[7] = { 22, 21, 24, 20, 18, 25, 23 };
	int nMax = pWaiting[1];
	int nPosMax = 0;
	
	for (int i = 1; i < 7; i++) {
		if (nMax == 20) {
			break;
		}

		if (pWaiting[i] % 2 != 0) {
			continue;
		}

		if (nMax < pWaiting[i]) {
			nMax = pWaiting[i];
			nPosMax = i;
		}
	}

	cout << "최대값은" << nMax << "위치는" << nPosMax << "번째 입니다." << endl;

	return 0;
}