#include "framework.h"
#include "CState_Mons.h"
#include "CAI.h"
#include "CMonster.h"
#include "SelectGDI.h"

CState_Mons::CState_Mons(eSTATE_MONS state)
{
	m_pOwner = nullptr;
	m_eMonsState = state;
}

CState_Mons::~CState_Mons()
{
}

CAI* CState_Mons::getOwner()
{
	return m_pOwner;
}

eSTATE_MONS CState_Mons::getState()
{
	return m_eMonsState;
}

CMonster* CState_Mons::getMonster()
{
	return m_pOwner->getOwner();
}
