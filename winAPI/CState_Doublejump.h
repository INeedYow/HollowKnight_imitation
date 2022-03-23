#pragma once
#include "CState_Player.h"
class CState_Doublejump : public CState_Player
{
	float	m_fTimer;
	float	m_fAccel;

public:
	CState_Doublejump(eSTATE_PLAYER state);
	virtual ~CState_Doublejump();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

