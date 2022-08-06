#pragma once
#include "CState_Mons.h"
class CState_Fly_Idle :public CState_Mons
{
	float	m_fTimer;

public:
	CState_Fly_Idle(eSTATE_MONS state);
	~CState_Fly_Idle();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

