#pragma once
#include "CState_Mons.h"
class CState_Attack :  public CState_Mons
{


public:
	CState_Attack(eSTATE_MONS state);
	~CState_Attack();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

