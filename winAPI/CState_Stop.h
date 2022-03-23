#pragma once
#include "CState_Mons.h"

class CState_Stop : public CState_Mons
{
	float m_fTimer;

public:
	CState_Stop(eSTATE_MONS state);
	~CState_Stop();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);

};

