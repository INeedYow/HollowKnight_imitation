#pragma once
#include "CState_Player.h"

class CState_Idle : public CState_Player
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

