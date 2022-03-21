#include "framework.h"
#include "CState_Upslash.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Upslash::CState_Upslash(eSTATE_PLAYER state)
	: CState(state) 
{
	m_fAttackDelay = 0.f;
}

CState_Upslash::~CState_Upslash()
{
}

void CState_Upslash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	if (chk & SP_AIR)
	{
		if (info.fGravity < P_GRAVMAX)
			info.fGravity += P_GRAV * fDT;

		pos.y += info.fGravity * fDT;
	}

	if (m_fAttackDelay > (float)P_ATTDELAY)
	{
		if (chk & SP_AIR)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FALL);
		}
		else
		{
			changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
		}
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Upslash::enter()
{
	getPlayer()->upSlash();
	getPlayer()->playAnim(L"UpSlash");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Upslash::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
	m_fAttackDelay = 0.f;
}

void CState_Upslash::printInfo(HDC hDC)
{
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);
	LPCWSTR	strInfo = L"UpSlash";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
