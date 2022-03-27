#pragma once
#include "CState_Mons.h"
class CState_BSkill : public CState_Mons
{
	float	m_fDura;
	//float	m_fSpd;
	//float	m_fRad;

public:
	CState_BSkill(eSTATE_MONS state);
	~CState_BSkill();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

