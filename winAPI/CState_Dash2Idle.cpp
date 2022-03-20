#include "framework.h"
#include "CState_Dash2Idle.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Dash2Idle::CState_Dash2Idle(eSTATE_PLAYER state)
	: CState(state)
{
	m_fDura = 0.f;
}

CState_Dash2Idle::~CState_Dash2Idle()
{
}

void CState_Dash2Idle::update(UINT& chk)
{
	m_fDura -= fDT;

	if (m_fDura < 0.f)
	{
		changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
	}
}

void CState_Dash2Idle::enter()
{
	getPlayer()->playAnim(L"Dash2Idle");
	getPlayer()->setCheck(SP_STOPANIM, true);
	m_fDura = 0.17f;
}

void CState_Dash2Idle::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
	m_fDura = 0.f;
}