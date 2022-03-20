#pragma once
#include "CState.h"
class CState_Downslash :    public CState
{
	float m_fAttackDelay;

public:
	CState_Downslash(eSTATE_PLAYER state);
	virtual ~CState_Downslash();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
};

