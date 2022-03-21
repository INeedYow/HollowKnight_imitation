#pragma once
#include "CState.h"
class CState_Fire : public CState
{
	float	m_fAttackDelay;

	float	m_fSoul;
	float	m_fDecreaseSpd;
	UINT	m_uiResultSoul;

public:
	CState_Fire(eSTATE_PLAYER state);
	virtual ~CState_Fire();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

