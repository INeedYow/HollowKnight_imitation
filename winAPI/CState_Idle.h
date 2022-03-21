#pragma once
#include "CState.h"

class CState_Idle : public CState
{
	float	m_fTimer;

public:
	CState_Idle(eSTATE_PLAYER state);	// CState���� ������ ������ �ؼ�
	virtual ~CState_Idle();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

