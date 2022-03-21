#pragma once
#include "CState.h"
class CState_Upslash :    public CState
{
	float m_fAttackDelay;

public:
	CState_Upslash(eSTATE_PLAYER state);
	virtual ~CState_Upslash();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

