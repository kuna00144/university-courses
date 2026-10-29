#include <iostream>
using namespace std;

double FindClosetPoint(double* pSample, int nSizeOfArray, double target, double& nearest);
int FindClosetPoint(int* pSample, int nSizeOfArray, int target, int& nearest, bool bAbsDiff = true);

int main() {
	cout << "20201599 이건아" << endl;

	const int nSizeOfArray = 5;

	/* double pSample[nSizeOfArray] = { 0.3, 0.6, 0.1, 0.4, 0.8 };
	double target, diff, nearest;

	cout << "0과 1 사이의 숫자를 입력해주세요." << endl;
	cin >> target;

	diff = FindClosetPoint(pSample, nSizeOfArray, target, nearest);

	cout << "가장 근접한 값은" << nearest << "그 차이는" << diff << "입니다." << endl; */

	int pSample[nSizeOfArray] = { 3, 6, 1, 4, 8 };
	int iTarget, iDiff, iNearest;
	cout << "1과 10 사이의 숫자를 입력해주세요." << endl;
	cin >> iTarget;

	iDiff = FindClosetPoint(pSample, nSizeOfArray, iTarget, iNearest);

	cout << "가장 근접한 값은" << iNearest << "그 차이는" << iDiff << "입니다." << endl;

}

double FindClosetPoint(double* pSample, int nSizeOfArray, double target, double& nearest) {
	double minDiff = 1;
	double diff = 1;

	for (int i = 0; i < nSizeOfArray; i++) {
		double val = pSample[i];
		diff = abs(target - val);

		if (diff < minDiff) {
			minDiff = diff;
			nearest = val;
		}
	}

	return minDiff;
}

int FindClosetPoint(int* pSample, int nSizeOfArray, int target, int& nearest, bool bAbsDiff) {
	int minDiff = 10;
	int diff;

	for (int i = 0; i < nSizeOfArray; i++) {
		int val = pSample[i];
		
		if (bAbsDiff) {
			diff = abs(target - val);
		}
		else{
			diff = target - val;
		}

		if (diff < minDiff) {
			minDiff = diff;
			nearest = val;
		}
	}

	return minDiff;
}