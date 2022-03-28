#pragma once
#include "CState_Mons.h"
class CState_Shoot :  public CState_Mons
{
	float m_fDura;

public:
	CState_Shoot(eSTATE_MONS state);
	~CState_Shoot();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

