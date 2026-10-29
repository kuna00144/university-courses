#include "CDyna.h"
#include <iostream>
using namespace std;
namespace Gal {
    CDyna::CDyna() {
        m_nSize = 0;
        m_pnSchedule = NULL;
    }
    CDyna::~CDyna() {
        if (m_pnSchedule != NULL) {
            delete[] m_pnSchedule;  // 동적으로 할당한 메모리를 해제합니다.
        }
    }

    void CDyna::ShowSchedule() {
        if (m_pnSchedule == NULL) {
            cout << "NULL..." << endl;  // 스케줄이 NULL인 경우 "NULL..."을 출력합니다.
        }
        else {
            for (int i = 0; i < m_nSize; i++) {
                cout << m_pnSchedule[i] << " ";  // 스케줄의 내용을 출력합니다.
            }
            cout << endl;
        }
    }

    void CDyna::SetInfo(int nSize, int* pSch) {
        m_nSize = nSize;  // 스케줄의 크기를 설정합니다.
        if (m_pnSchedule != NULL) {
            delete[] m_pnSchedule;  // 동적으로 할당한 기존의 스케줄을 해제합니다.
        }
        m_pnSchedule = new int[nSize];  // 스케줄의 크기만큼 새로운 메모리를 할당합니다.
        for (int i = 0; i < nSize; i++) {
            m_pnSchedule[i] = pSch[i];  // 주어진 배열의 내용을 스케줄로 복사합니다.
        }
    }
}

