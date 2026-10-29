#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include "CMoney.h"
using namespace std;
const CMoney operator+(const CMoney& amount1, const CMoney& amount2);

int main()
{
    cout << "20201599 이건아" << endl;
    CMoney aMoney(14, 23), bMoney(7, 84), sumMoney; // aMoney -> amount1, bMoney -> amount2
    sumMoney = aMoney + bMoney; // 이거 역할이 sumMoney = +(aMoney, bMoney) 처럼 operator역할이랑 같아서 아래에서 나오는 return 값이 sumMoney에 저장되는거
    cout << "total $" << sumMoney.GetDollar() << "." << sumMoney.GetCent() << endl;
}

// const가 return type 앞에 붙은 이유 : 연산 진행하고 return한 값을 고정하겠다
const CMoney operator+(const CMoney& amount1, const CMoney& amount2) // amount1, 2에 대한 값을 바꾸지 않겠다는 이유로 const 씀
{
    int allCents1 = amount1.GetCent() + amount1.GetDollar() * 100;
    int allCents2 = amount2.GetCent() + amount2.GetDollar() * 100;
    int sumAllCents = allCents1 + allCents2;

    int absAllCents = abs(sumAllCents);
    int finalDollars = absAllCents / 100; // 나누기 연산자
    int finalCents = absAllCents % 100;   // 나머지 연산자
        
    if (sumAllCents < 0) {
        finalDollars = -finalDollars;
        finalCents = -finalCents;
    }

    return CMoney(finalDollars, finalCents);
}