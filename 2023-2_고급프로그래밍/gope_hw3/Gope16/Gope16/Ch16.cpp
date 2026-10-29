#include <iostream>
#include "a.h"
using namespace std;


int main() {
	cout << "20201599 ÀÌ°Ç¾Æ" << endl;
	CPair<int> intCPair(4, 10);
	CPair<char> charCPair('e', 'i');

	cout << "intCPair first : " << intCPair.getFirst() << "\nintCPair second :" << intCPair.getSecond() << endl;
	cout << "charCPair first : " << charCPair.getFirst() << "\ncharCPair second :" << charCPair.getSecond() << endl;

	return 0;
}