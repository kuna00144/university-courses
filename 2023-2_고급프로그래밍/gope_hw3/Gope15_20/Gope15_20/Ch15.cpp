#include <iostream>
#include "sale.h"
#include "discountsale.h"
using namespace std;
using namespace SavitchSale;

int main() {
	cout << "20201599 ÀÌ°Ç¾Æ" << endl;
	Sale Sale1(65);
	Sale Sale2(70);
	DiscountSale dcSale1(80, 10);
	DiscountSale dcSale2(90, 30);

	if (Sale1 < Sale2) {
		cout << "Sale2 is good" << endl;
	}
	else {
		cout << "Sale1 is good" << endl;
	}

	Sale1.savings(Sale2);
	cout << Sale1.getPrice() << endl;

	if (dcSale1 < dcSale2) {
		cout << "dcSale2 is good" << endl;
	}
	else {
		cout << "dcSale1 is good" << endl;
	}

	dcSale1.savings(dcSale2);

	cout << dcSale1.getPrice() << endl;
	
	return 0;
}
