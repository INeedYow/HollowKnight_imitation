#pragma once
#include "CState_Player.h"
class CState_Jump :    public CState_Player
{
	float	m_fTimer;

public:
	CState_Jump(eSTATE_PLAYER state);	// CState���� ������ ������ �ؼ�
	virtual ~CState_Jump();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

