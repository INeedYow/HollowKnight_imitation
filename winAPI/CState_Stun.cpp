#include "framework.h"
#include "CState_Stun.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Stun::CState_Stun(eSTATE_PLAYER state)
	: CState(state)
{
	m_fvDir = {};
	m_fDura = 0.f;
	m_fSpd = 100.f;
}

CState_Stun::~CState_Stun()
{
}

void CState_Stun::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fDura -= fDT;

	if (m_fDura < 0.f)
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

	m_fvDir = m_fvDir.normalize();

	pos.x += m_fvDir.x * m_fSpd * fDT;

	if (chk & SP_AIR)
	{
		pos.y += m_fvDir.y * m_fSpd * fDT;

		if (info.fSpdY < 0.f)
			chk |= SP_GODOWN;
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Stun::enter()
{
	getPlayer()->playAnim(L"Stun");
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_NODMG, true);
	m_fvDir = getPlayer()->getPlayerInfo().fvKnockBackDir;

	tPlayerInfo info = getPlayer()->getPlayerInfo();

	//if (info.fGravity < info.fSpdY)
	//	info.fGravity = info.fSpdY;
	info.fNoDmgTimer = 2.0f + (float)P_STUNDURA;

	getPlayer()->setPlayerInfo(info);

	m_fDura = (float)P_STUNDURA;
}

void CState_Stun::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);

	m_fDura = 0.f;
	m_fvDir = {};
}

void CState_Stun::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC18);
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Stun";
	wchar_t bufDura[255] = {};

	swprintf_s(bufDura, L"x = %.2f", m_fDura);

	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 105, bufDura, (int)wcslen(bufDura));
}
