#include <iostream>
#include "CMoney.h"
using namespace std;
//const CMoney operator+(const CMoney& amount1, const CMoney& amount2);

int main()
{
    cout << "20201599 이건아" << endl;
    CMoney aMoney(14, 23), bMoney(7, 84), sumMoney;
    sumMoney = aMoney + bMoney;
    cout << "total $" << sumMoney.GetDollar() << "." << sumMoney.GetCent() << endl;
}

const CMoney operator+(const CMoney& amount1, const CMoney& amount2)
{
    int allCents1 = amount1.GetCent() + amount1.GetDollar() * 100;
    int allCents2 = amount2.GetCent() + amount2.GetDollar() * 100;
    int sumAllCents = allCents1 + allCents2;
    int absAllCents = abs(sumAllCents);
    int finalDollars = absAllCents / 100; // 나누기 연산자
    int finalCents = absAllCents % 100;   // 나머지 연산자
    if (sumAllCents < 0)
    {
        finalDollars = -finalDollars;
        finalCents = -finalCents;
    }

    return CMoney(finalDollars, finalCents);
}