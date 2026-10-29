#pragma once
#include <iostream>
using namespace std;

class CMoney {
public:
    CMoney(); // 기본 생성자
    CMoney(int nDollar, int nCent);
    friend ostream & operator << (ostream & outputStream, const CMoney& aMoney);
    int GetDollar() const; // 멤버변수를 바꾸지 않는 상수 함수
    void SetDollar(int nDollar);
    int GetCent() const; // 상수 함수
    void SetCent(int nCent);
private:
    int m_nDollar; // 멤버 변수 생성
    int m_nCent;
};