#pragma once
#include "CState_Player.h"

class CState_Dash :    public CState_Player
{
	float	m_fDura;
	float	m_fSpd;
	float	m_fDecel;

public:
	CState_Dash(eSTATE_PLAYER state);
	virtual ~CState_Dash();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

