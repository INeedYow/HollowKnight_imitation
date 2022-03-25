#pragma once
#include "CState_Mons.h"
class CState_Die :  public CState_Mons
{
	float m_fTimer;

public:
	CState_Die(eSTATE_MONS state);
	~CState_Die();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

