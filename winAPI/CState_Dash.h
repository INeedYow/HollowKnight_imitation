#pragma once
#include "CState.h"
class CState_Dash :    public CState
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

