#pragma once
#include "CState_Player.h"
class CState_Upslash :    public CState_Player
{
	float m_fAttackDelay;

public:
	CState_Upslash(eSTATE_PLAYER state);
	virtual ~CState_Upslash();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

