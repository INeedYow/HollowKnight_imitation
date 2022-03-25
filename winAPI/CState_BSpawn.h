#pragma once
#include "CState_Mons.h"
class CState_BSpawn : public CState_Mons
{
	float m_fDura;

public:
	CState_BSpawn(eSTATE_MONS state);
	~CState_BSpawn();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

