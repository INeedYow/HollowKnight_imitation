#pragma once
#include "CState_Player.h"
class CState_Slash :    public CState_Player
{
	float m_fAttackDelay;

public:
	CState_Slash(eSTATE_PLAYER state);
	virtual ~CState_Slash();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};