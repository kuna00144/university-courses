#pragma once

template<class T>
class CPair {
public:
	CPair();
	CPair(T firstVal, T secondVal);
	void setFirst(T nFirst);
	void setSecond(T nSecond);
	T getFirst() const;
	T getSecond() const;
private:
	T first;
	T second;
};