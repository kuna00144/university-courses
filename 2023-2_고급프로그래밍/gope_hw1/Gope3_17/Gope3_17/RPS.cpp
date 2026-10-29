#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;

	int aiRand;
	string userStr;
	string aiStrRand;
	cout << "가위바위보 게임을 시작하겠습니다." << endl;
	cout << "R(Rock), P(Paper), S(Scissors) 중 하나를 고르시오." << endl;
	cin >> userStr;

	srand(time(0));
	aiRand = rand() % 3;

	switch (aiRand) {
		case 0:
			aiStrRand = "R";
			break;
		case 1:
			aiStrRand = "P";
			break;
		case 2:
			aiStrRand = "S";
			break;
	}

	cout << "컴퓨터는" << aiStrRand << "를 선택했고 사용자님은" << userStr << "를 선택하셨습니다." << endl;

	if (userStr == "R" && aiStrRand == "S" || userStr == "P" && aiStrRand == "R" || userStr == "S" && aiStrRand == "P") {
		cout << "축하" << endl;
	}
	else if (userStr == aiStrRand) {
		cout << "비겼습니다" << endl;
	}
	else {
		cout << "분발" << endl;
	}
	
	return 0;
}