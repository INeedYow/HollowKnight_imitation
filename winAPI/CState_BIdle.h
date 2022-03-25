#pragma once
#include "CState_Mons.h"
class CState_BIdle :   public CState_Mons
{
	float m_fDura;

public:
	CState_BIdle(eSTATE_MONS state);
	~CState_BIdle();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

