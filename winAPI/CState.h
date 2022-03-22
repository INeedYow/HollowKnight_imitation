#pragma once

#include "SelectGDI.h"

class CAI;
class CPlayer;

enum class eSTATE_PLAYER;

class CState
{
	friend class CAI;

private:
	CAI*			m_pOwner;
	eSTATE_PLAYER	m_ePlayerState;

public:
	CState(eSTATE_PLAYER state);
	virtual ~CState();

	CAI* getOwner();
	eSTATE_PLAYER getState();
	CPlayer* getPlayer();

	virtual void update(UINT& chk) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void printInfo(HDC hDC) = 0;
};