#pragma once
#include "CState.h"
class CState_Jump :    public CState
{
	float	m_fTimer;

public:
	CState_Jump(eSTATE_PLAYER state);	// CState에서 생성자 재정의 해서
	virtual ~CState_Jump();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

