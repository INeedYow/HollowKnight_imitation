#pragma once
#include "CState_Player.h"
class CState_Slash2 : public CState_Player
{
	float m_fAttackDelay;

public:
	CState_Slash2(eSTATE_PLAYER state);
	virtual ~CState_Slash2();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

