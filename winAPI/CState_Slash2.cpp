#include "framework.h"
#include "CState_Slash2.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Slash2::CState_Slash2(eSTATE_PLAYER state)
	: CState_Player(state)
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
		changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
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
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Slash2";
	wchar_t bufDelay[255] = {};

	swprintf_s(bufDelay, L"delay = %.1f", m_fAttackDelay);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDelay, (int)wcslen(bufDelay));
}
