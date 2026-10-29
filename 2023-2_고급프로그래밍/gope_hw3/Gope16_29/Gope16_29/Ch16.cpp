#include <iostream>
#include "Template.h"
using namespace std;

template<class T>
int main() {
	CPair<int> intCPair;
	CPair<char> charCPair;
	intCPair.setFirst(4);
	intCPair.setSecond(10);
	charCPair.setFirst('e');
	charCPair.setSecond('i');

	cout << "intCPair first : " << intCPair.getFirst() << "\nintCPair second :" << intCPair.getSecond() << endl;
	cout << "charCPair first : " << charCPair.getFirst() << "\ncharCPair second :" << charCPair.getSecond() << endl;

	return 0;
}