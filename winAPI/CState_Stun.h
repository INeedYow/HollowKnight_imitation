#pragma once
#include "CState.h"
class CState_Stun : public CState
{
	// TODO 피해경직은 끝나도 무적효과는 지속되게 하는법
	float m_fInvinsibleTimer;

	fVec2 m_fvDir;
	float m_fTimer;
	float m_fSpd;

public:
	CState_Stun(eSTATE_PLAYER state);
	virtual ~CState_Stun();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
};

