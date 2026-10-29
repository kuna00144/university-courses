#include <iostream>
#include "CMoney.h"
using namespace std;

int main() {
	cout << "20201599 ÀÌ°Ç¾Æ" << endl;
	CMoney aMoney(14, 23);
	CMoney bMoney(7, 84);
	CMoney cMoney = aMoney + bMoney;
	cout << "total &" << cMoney.GetDollar() << "." << cMoney.GetCent() << endl;
	return 0;
}