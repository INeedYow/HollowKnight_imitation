#pragma once
#include "CState.h"
class CState_Focus : public CState
{
	float m_fTimer;
	
	float m_fSoul;
	float m_fDecreaseSpd;

public:
	CState_Focus(eSTATE_PLAYER state);
	virtual ~CState_Focus();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
};

