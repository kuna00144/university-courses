#include <iostream>
using namespace std;

int main() {

	cout << "20201599 ÀÌ°Ç¾Æ" << endl;

	double price;
	price = 78.5;

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "The price is $" << price << endl;
}