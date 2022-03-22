#pragma once
#include "CState.h"
class CState_Fire : public CState
{
	float	m_fAttackDelay;

	float	m_fSoul;
	float	m_fDecreaseSpd;
	UINT	m_uiResultSoul;			// 영혼 소모를 시간에 걸쳐 줄어들게 할거라서 미리 결과값은 저장

public:
	CState_Fire(eSTATE_PLAYER state);
	virtual ~CState_Fire();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

