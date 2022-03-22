#include "framework.h"
#include "CState_Slash1.h"
#include "CAI.h"
#include "CPlayer.h"

#include "CEffect.h"

CState_Slash1::CState_Slash1(eSTATE_PLAYER state)
	: CState(state)
{
	m_fAttackDelay = 0.f;
}

CState_Slash1::~CState_Slash1()
{
}

// TODO slash2
void CState_Slash1::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	if (chk & SP_AIR)
	{	// 공중에서 공격할 때 중력적용
		info.fSpdY -= info.fGravity * fDT;

		if (info.fSpdY <= 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;

		/*if (info.fGravity < P_SPDY_MIN)
			info.fGravity += P_GRAV * fDT;*/

		//if (info.fGravity < info.fSpdY)
		//	info.fGravity = info.fSpdY;

		pos.y -= (info.fSpdY /*- info.fGravity*/) * fDT;
	}
	else
	{
		// TODO Slash2
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

void CState_Slash1::enter()
{
	getPlayer()->firstSlash();
	getPlayer()->playAnim(L"Slash1");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Slash1::exit()
{
	m_fAttackDelay = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);
}

void CState_Slash1::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC18);
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Slash1";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
