#include "framework.h"
#include "CState_Slash2.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Slash2::CState_Slash2(eSTATE_PLAYER state)
	: CState(state)
{
	m_fAttackDelay = 0.f;
}

CState_Slash2::~CState_Slash2()
{
}

void CState_Slash2::update(UINT& chk)
{
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	if (m_fAttackDelay > (float)P_ATTDELAY)
	{
		changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
		
	}

	getPlayer()->setPlayerInfo(info);
}

void CState_Slash2::enter()
{
	getPlayer()->secondSlash();
	getPlayer()->playAnim(L"Slash2");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Slash2::exit()
{
	m_fAttackDelay = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);
}

void CState_Slash2::printInfo(HDC hDC)
{
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);
	LPCWSTR	strInfo = L"Slash2";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
