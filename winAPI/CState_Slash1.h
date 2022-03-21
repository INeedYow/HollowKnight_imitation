#pragma once
#include "CState.h"
class CState_Slash1 :    public CState
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