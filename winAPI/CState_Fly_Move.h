#pragma once
#include "CState_Mons.h"
class CState_Fly_Move : public CState_Mons
{
	float	m_fTimer;

public:
	CState_Fly_Move(eSTATE_MONS state);
	~CState_Fly_Move();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

