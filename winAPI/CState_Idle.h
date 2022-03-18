#pragma once
#include "CState.h"

class CState_Idle : public CState
{

public:
	CState_Idle(eSTATE_PLAYER state);	// CState에서 생성자 재정의 해서
	virtual ~CState_Idle();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

