#pragma once

#include "SelectGDI.h"

class CAI;
class CMonster;

enum class eSTATE_MONS;

class CState_Mons
{
	friend class CAI;

private:
	CAI*			m_pOwner;
	eSTATE_MONS		m_eMonsState;

public:
	CState_Mons(eSTATE_MONS state);
	virtual ~CState_Mons();

	CAI* getOwner();
	eSTATE_MONS getState();
	CMonster* getMonster();

	virtual void update(UINT& chk) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void printInfo(HDC hDC) = 0;
};

