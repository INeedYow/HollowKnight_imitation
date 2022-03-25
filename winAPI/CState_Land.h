#pragma once
#include "CState_Player.h"
class CState_Land :   public CState_Player
{
	float m_fDura;

public:
	CState_Land(eSTATE_PLAYER state);
	virtual ~CState_Land();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

