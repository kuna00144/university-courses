#pragma once

class CMoney {
public:
	CMoney();
	CMoney(int nDollar, int nCent);
	int GetDollar() const; // 멤버변수를 바꾸지 않는 상수 함수
	void SetDollar(int nDollar);
	int GetCent() const; // 상수 함수
	void SetCent(int nCent);
	CMoney operator +(const CMoney& amount); // 그래서 return type이 CMoney 
private:
	int m_nDollar;
	int m_nCent;
};