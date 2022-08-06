#pragma once
#include "CState_Mons.h"

class CState_Stand : public CState_Mons
{
	float m_fTimer;

public:
	CState_Stand(eSTATE_MONS state);
	~CState_Stand();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

