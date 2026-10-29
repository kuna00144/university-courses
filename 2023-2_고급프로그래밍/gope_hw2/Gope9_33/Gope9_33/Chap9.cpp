#include <iostream>
#include <cstring>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	char chString1[30] = "Hello", chString2[30];
	strcpy_s(chString2, "Kim"); // strcpy : 뒤에 내용을 앞에 복사해옴

	cout << "chString1 = " << chString1 << " / chString2 = " << chString2 << endl;

	if (strcmp(chString1, chString2) == 0){
		cout << "두 String이 같습니다. " << endl;
	}
	else {
		cout << "두 String이 다릅니다." << endl;
	}

	cout << "새 chString2를 입력해주세요. : " << endl;
	cin >> chString2;
	strcat_s(chString1, chString2); // strcat : 앞에꺼에 뒤에꺼 이어붙임
	cout << chString1 << endl;

	cin.ignore(30, '\n'); // 이렇게 getline써주기 전에 ignore을 써주어야 한다.
	cin.getline(chString2, 30);
	cout << "새로운 chString2 = " << chString2 << endl;

	return 0;
}