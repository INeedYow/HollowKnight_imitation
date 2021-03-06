#pragma once
#include "CState_Player.h"
class CState_Stun : public CState_Player
{
	fVec2 m_fvDir;
	float m_fDura;
	float m_fSpd;

public:
	CState_Stun(eSTATE_PLAYER state);
	virtual ~CState_Stun();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

