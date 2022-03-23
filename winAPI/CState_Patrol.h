#pragma once
#include "CState_Mons.h"
class CState_Patrol :    public CState_Mons
{
	float m_fTimer;

public:
	CState_Patrol(eSTATE_MONS state);
	~CState_Patrol();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

