#pragma once
#include "CState_Mons.h"
class CState_BMove :  public CState_Mons
{
	int m_ix;
	int m_iy;
	int m_iX;
	int m_iY;				// ���� �̵����� �ִ��ּ� ��ǥ�� (rect�� �׸��Ŷ� ���� ���� float 4����)

	iPoint m_ipDest;		// ������ǥ

	float m_fDura;

public:
	CState_BMove(eSTATE_MONS state);
	~CState_BMove();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

