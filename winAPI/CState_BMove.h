#pragma once
#include "CState_Mons.h"
class CState_BMove :  public CState_Mons
{
	int m_ix;
	int m_iy;
	int m_iX;
	int m_iY;				// 보스 이동영역 최대최소 좌표들 (rect로 그릴거라서 쓰기 쉽게 float 4개씀)

	iPoint m_ipDest;		// 목적좌표

	float m_fDura;

public:
	CState_BMove(eSTATE_MONS state);
	~CState_BMove();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

