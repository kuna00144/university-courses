#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

int AmIWin(string strRPCInput, string strRPCCom);

int main() {
	cout << "20201599 이건아" << endl;

	int aiRand;
	int nWin;
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

	nWin = AmIWin(userStr, aiStrRand);

	cout << "컴퓨터는" << aiStrRand << "를 선택했고 사용자님은" << userStr << "를 선택하셨습니다." << endl;

	switch (nWin)
	{
		case 1:
			cout << "사용자님이 승리하였습니다." << endl;
			break;
		case -1:
			cout << "사용자님이 패배하였습니다." << endl;
			break;
		case 0:
			cout << "비겼습니다." << endl;
			break;
		default:
			cout << "바보" << endl;
			break;
	}

	return 0;
}

int AmIWin(string strRPCInput, string strRPCCom) {
	
	int nWin;

	if (strRPCInput == "R" && strRPCCom == "S" || strRPCInput == "P" && strRPCCom == "R" || strRPCInput == "S" && strRPCCom == "P") {
		nWin = 1;
	}
	else if (strRPCInput == "R" && strRPCCom == "P" || strRPCInput == "P" && strRPCCom == "S" || strRPCInput == "S" && strRPCCom == "R") {
		nWin = -1;
	}
	else if (strRPCInput == strRPCCom) {
		nWin = 0;
	}
	else {
		nWin = -8;
	}

	return nWin;
}