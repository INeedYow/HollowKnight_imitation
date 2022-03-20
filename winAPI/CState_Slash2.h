#pragma once
#include "CState.h"
class CState_Slash2 : public CState
{
	float m_fAttackDelay;

public:
	CState_Slash2(eSTATE_PLAYER state);
	virtual ~CState_Slash2();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
};

