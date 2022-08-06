#pragma once
#include "CState_Mons.h"
class CState_Move : public CState_Mons
{

public:
	CState_Move(eSTATE_MONS state);
	~CState_Move();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

