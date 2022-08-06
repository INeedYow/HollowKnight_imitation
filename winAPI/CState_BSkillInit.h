#pragma once
#include "CState_Mons.h"
class CState_BSkillInit : public CState_Mons
{
	float	m_fDura;
	float	m_fSpd;

public:
	CState_BSkillInit(eSTATE_MONS state);
	~CState_BSkillInit();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

