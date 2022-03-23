#pragma once

#include "SelectGDI.h"

class CStatus;
class CPlayer;

enum class eSTATE_PLAYER;

class CState_Player
{
	friend class CStatus;

private:
	CStatus*		m_pOwner;
	eSTATE_PLAYER	m_ePlayerState;

public:
	CState_Player(eSTATE_PLAYER state);
	virtual ~CState_Player();

	CStatus* getOwner();
	eSTATE_PLAYER getState();
	CPlayer* getPlayer();

	virtual void update(UINT& chk) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void printInfo(HDC hDC) = 0;
};