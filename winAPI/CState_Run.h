#pragma once
#include "CState.h"
class CState_Run :    public CState
{
public:
	CState_Run(eSTATE_PLAYER state);	// CState���� ������ ������ �ؼ�
	virtual ~CState_Run();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
};

