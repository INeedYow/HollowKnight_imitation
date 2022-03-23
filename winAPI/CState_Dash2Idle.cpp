#include "framework.h"
#include "CState_Dash2Idle.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Dash2Idle::CState_Dash2Idle(eSTATE_PLAYER state)
	: CState_Player(state)
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
		changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}
}

void CState_Dash2Idle::enter()
{
	getPlayer()->playAnim(L"Dash2Idle");
	getPlayer()->setCheck(SP_STOPANIM, true);
	m_fDura = 0.2f;
}

void CState_Dash2Idle::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
	m_fDura = 0.f;
}

void CState_Dash2Idle::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Dash2Idle";
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
}
