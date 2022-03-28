#pragma once
#include "CState_Player.h"
class CState_Run :    public CState_Player
{
	float m_fTimer = 0.f;

public:
	CState_Run(eSTATE_PLAYER state);	// CState���� ������ ������ �ؼ�
	virtual ~CState_Run();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

