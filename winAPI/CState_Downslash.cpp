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

// TODO 하단 공격 시 점프
void CState_Downslash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	//if (info.fGravity < P_SPDY_MIN)
	//	info.fGravity += P_GRAV * fDT;

	/*if (info.fGravity < info.fSpdY)
		info.fGravity = info.fSpdY;*/
	info.fSpdY -= info.fGravity * fDT;

	if (info.fSpdY <= 0.f)
		chk |= SP_GODOWN;

	if (info.fSpdY < (float)P_SPDY_MIN)
		info.fSpdY = (float)P_SPDY_MIN;

	pos.y -= (info.fSpdY /*- info.fGravity*/) * fDT;
	

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

void CState_Downslash::printInfo(HDC hDC)
{
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"DownSlash";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
