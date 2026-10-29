#include <iostream>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	int* p3, * p4;
	p3 = new int;
	p4 = new int;

	cout << "p3 : " << p3 << endl;
	cout << "p4 : " << p4 << endl;
	cout << "*p3 : " << *p3 << endl;
	cout << "*p4 : " << *p4 << endl;

	*p3 = 7;
	*p4 = 8;
	cout << "p3 : " << p3 << endl;
	cout << "p4 : " << p4 << endl;
	cout << "*p3 : " << *p3 << endl;
	cout << "*p4 : " << *p4 << endl;

	p3 = p4;
	cout << "p3 : " << p3 << endl;
	cout << "p4 : " << p4 << endl;
	cout << "*p3 : " << *p3 << endl;
	cout << "*p4 : " << *p4 << endl;

	delete p3;
	// delete p4;
	// why: 이미 p3에서 p4와 같은 주소를 가지고 있다가 공간을 지워서 한번 더 지우려고 하면 에러남
	return 0;
}