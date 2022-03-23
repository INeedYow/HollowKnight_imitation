#pragma once
#include "CState_Player.h"
class CState_Slash1 :    public CState_Player
{
	float m_fAttackDelay;

public:
	CState_Slash1(eSTATE_PLAYER state);
	virtual ~CState_Slash1();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};