#pragma once
#include "CState_Player.h"
class CState_Focus : public CState_Player
{
	float m_fTimer;
	
	float m_fSoul;
	float m_fDecreaseSpd;

public:
	CState_Focus(eSTATE_PLAYER state);
	virtual ~CState_Focus();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

