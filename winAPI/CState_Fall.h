#pragma once
#include "CState_Player.h"
class CState_Fall :    public CState_Player
{
public:
	CState_Fall(eSTATE_PLAYER state);	// CState���� ������ ������ �ؼ�
	virtual ~CState_Fall();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

