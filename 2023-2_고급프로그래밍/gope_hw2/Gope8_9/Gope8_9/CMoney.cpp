#include "CMoney.h"

CMoney::CMoney() { // 기본 생성자
    m_nDollar = 0; // 멤버 변수
    m_nCent = 0;
}

CMoney::CMoney(int nDollar, int nCent) {
    m_nDollar = nDollar;
    m_nCent = nCent;
}

int CMoney::GetDollar() const {
    return m_nDollar;
}

void CMoney::SetDollar(int nDollar) {
    m_nDollar = nDollar;
}

int CMoney::GetCent() const {
    return m_nCent;
}

void CMoney::SetCent(int nCent) {
    m_nCent = nCent;
}