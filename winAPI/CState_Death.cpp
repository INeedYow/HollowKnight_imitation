#include "framework.h"
#include "CState_Death.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Death::CState_Death(eSTATE_PLAYER state)
	: CState(state)
{
	m_fDura = 0.f;
}

CState_Death::~CState_Death()
{
}

void CState_Death::update(UINT& chk)
{
	m_fDura -= fDT;

	// TODO
	if (m_fDura < 0.f)
	{
		changeAIState(getOwner(), eSTATE_PLAYER::FALL);
	}
}

void CState_Death::enter()
{
	m_fDura = 2.4f;
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_NODMG, true);
	getPlayer()->playAnim(L"Death");
}

void CState_Death::exit()
{
	m_fDura = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);

	// юс╫ц
	//getPlayer()->setCheck(SP_NODMG, false);
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.uiHP = 5;
	info.uiSoul = 0;
	getPlayer()->setPlayerInfo(info);
}
