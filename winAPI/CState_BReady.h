#pragma once
#include "CState_Mons.h"
class CState_BReady : public CState_Mons
{
	float	m_fDura;
	float	m_fSpd;

public:
	CState_BReady(eSTATE_MONS state);
	~CState_BReady();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

