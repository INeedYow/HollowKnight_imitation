#include "framework.h"
#include "CState_Downslash.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Downslash::CState_Downslash(eSTATE_PLAYER state)
	: CState(state)
{
	m_fAttackDelay = 0.f;
}

CState_Downslash::~CState_Downslash()
{
}

void CState_Downslash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	if (info.fGravity < P_GRAVMAX)
		info.fGravity += P_GRAV * fDT;

	pos.y -= (info.fSpdY - info.fGravity) * fDT;
	

	if (m_fAttackDelay > (float)P_ATTDELAY)
	{
		if (chk & SP_AIR)
		{
			
		}
		else
		{
			changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
		}
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Downslash::enter()
{
	getPlayer()->downSlash();
	getPlayer()->playAnim(L"DownSlash");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Downslash::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
}
