 #include <iostream>
using namespace std;

int main() {
	cout << "20201599 이건아" << endl;
	int* p1, * p2, v1 = 3, v2 = 4;
	p1 = 0;
	cout << p1 << endl; // p1의 주소
	cout << &v1 << endl;  // v1의 주소값
	
	p1 = &v1;
	cout << p1 << endl; // v1의 주소를 복사해와서 v1의 주소값 나옴
	cout << *p1 << endl; // v1의 값이 나옴

	p2 = &v2; // v2의 주소를 복사해옴
	*p1 = *p2; // p1의 값 3이 p2의 v2에서 가져온값 4로 변경됨
	cout << p1 << "," << p2 << "," << *p1 << "," << *p2 << endl;
	p1 = p2;
	cout << p1 << "," << p2 << "," << *p1 << "," << *p2 << endl;

	return 0;
}