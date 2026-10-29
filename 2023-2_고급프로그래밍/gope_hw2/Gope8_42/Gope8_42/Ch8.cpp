#include <iostream>
#include "CMoney.h"
using namespace std;

int main() {
    cout << "20201599 이건아" << endl;
    CMoney aMoney(14, 23), bMoney(7, 84);
    cout << aMoney << "+" << bMoney << endl;
}

// ostream 쓰는 이유
// 원래는 cout 일일이 해서 코드 복잡
// 아래 보면 outputStream에 차곡차곡 쌓아서 한번에 return
ostream &operator << (ostream &outputStream, const CMoney &aMoney)
{
    int absDollars = abs(aMoney.m_nDollar);
    int absCents = abs(aMoney.m_nCent);

    if (aMoney.m_nDollar < 0 || aMoney.m_nCent < 0){
        outputStream << "$-";
    }
    else {
        outputStream << "$";
    }

    outputStream << absDollars;
    if (absCents >= 10) {
        outputStream << "." << absCents;
    }
    else {
        outputStream << ".0" << absCents;
        outputStream << " ";
    }

    return outputStream;
}