#pragma once
#include "CState.h"

class CState_Idle : public CState
{

public:
	CState_Idle(eSTATE_PLAYER state);	// CState���� ������ ������ �ؼ�
	virtual ~CState_Idle();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

