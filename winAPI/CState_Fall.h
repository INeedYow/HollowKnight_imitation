#pragma once
#include "CState_Player.h"
class CState_Fall :    public CState_Player
{
public:
	CState_Fall(eSTATE_PLAYER state);	// CState에서 생성자 재정의 해서
	virtual ~CState_Fall();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

