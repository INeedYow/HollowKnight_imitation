#pragma once
#include "CState_Player.h"
class CState_Dash2Idle :public CState_Player
{
	float m_fDura;

public:
	CState_Dash2Idle(eSTATE_PLAYER state);
	virtual ~CState_Dash2Idle();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

