#pragma once
#include "CState.h"
class CState_Doublejump : public CState
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

