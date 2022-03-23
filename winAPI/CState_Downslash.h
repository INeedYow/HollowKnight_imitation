#pragma once
#include "CState_Player.h"
class CState_Downslash :    public CState_Player
{
	float m_fAttackDelay;

public:
	CState_Downslash(eSTATE_PLAYER state);
	virtual ~CState_Downslash();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

