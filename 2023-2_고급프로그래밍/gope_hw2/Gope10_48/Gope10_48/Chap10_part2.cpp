#include <iostream>
using namespace std;
#include "CDyna.h"
int main() {
    cout << "20201599 이건아" << endl;
    CDyna* pDyna;
    pDyna = new CDyna;  // CDyna 클래스의 인스턴스를 동적으로 생성하여 포인터에 저장합니다.

    int sche[3] = { 1, 2, 3 };  // 정수 배열 arr을 초기화합니다.
    pDyna->SetInfo(3, sche);  // CDyna 클래스의 SetInfo 함수를 호출하여 배열 크기와 내용을 설정합니다.
    pDyna->ShowSchedule();  // CDyna 클래스의 ShowSchedule 함수를 호출하여 스케줄을 출력합니다.

    CDyna anotherDyna;  // CDyna 클래스의 또 다른 인스턴스를 생성합니다.
    anotherDyna = *pDyna;  // 대입 연산자를 사용하여 cd 인스턴스의 내용을 anotherDyna 인스턴스에 복사합니다.

    anotherDyna.ShowSchedule();  // 복사된 스케줄을 출력합니다.
    delete pDyna;  // 동적으로 생성한 인스턴스를 삭제합니다.
    return 0;
}

CDyna& CDyna::operator=(const CDyna& rtSide)
{
    if (this == &rtSide) {  // 대입 연산자를 사용할 때, 자기 자신과 대입되는 객체가 같은지 확인합니다.
        return *this;  // 같다면 현재 객체를 그대로 반환합니다.
    }
    else {
        m_nSize = rtSide.m_nSize;  // 대입되는 객체의 크기를 현재 객체에 복사합니다.
        if (m_pnSchedule != NULL) {  // 현재 객체의 스케줄이 NULL이 아니라면
            delete[] m_pnSchedule;  // 동적으로 할당한 메모리를 해제합니다.
        }
        m_pnSchedule = new int[m_nSize];  // 대입되는 객체의 크기만큼 새로운 메모리를 할당합니다.
        for (int nIndex = 0; nIndex < m_nSize; nIndex++) {
            m_pnSchedule[nIndex] = rtSide.m_pnSchedule[nIndex];  // 대입되는 객체의 스케줄을 현재 객체로 복사합니다.
        }
    }
    return *this;  // 현재 객체를 반환합니다.
}