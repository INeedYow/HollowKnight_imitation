#pragma once
#include "CState.h"
class CState_Run :    public CState
{
public:
	CState_Run(eSTATE_PLAYER state);	// CState에서 생성자 재정의 해서
	virtual ~CState_Run();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
};

