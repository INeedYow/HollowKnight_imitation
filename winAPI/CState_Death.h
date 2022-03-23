#pragma once
#include "CState_Player.h"
class CState_Death : public CState_Player
{
	float	m_fDura;

public:
	CState_Death(eSTATE_PLAYER state);
	virtual ~CState_Death();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};