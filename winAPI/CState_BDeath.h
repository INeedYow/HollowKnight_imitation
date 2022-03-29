#pragma once
#include "CState_Mons.h"
class CState_BDeath : public CState_Mons
{
	float m_fDura;

public:
	CState_BDeath(eSTATE_MONS state);
	~CState_BDeath();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);

};

