#pragma once

namespace Gal {
	class CDyna {
	public:
		CDyna();
		~CDyna();
		CDyna& operator=(const CDyna& rtSide);
		void ShowSchedule();
		void SetInfo(int nSize, int* pSch);
	private:
		int m_nSize;
		int* m_pnSchedule; // 포인터 변수
	};
}
