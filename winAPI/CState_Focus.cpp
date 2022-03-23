#include "framework.h"
#include "CState_Focus.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Focus::CState_Focus(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fTimer = 0.f;
	m_fSoul = 0.f;
	m_fDecreaseSpd = (float)P_FIRESOUL / (float)P_FOCUSMAX;
}

CState_Focus::~CState_Focus()
{
}

void CState_Focus::update(UINT& chk)
{
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (KEY_OFF('A'))
	{
		changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}

	m_fTimer += fDT;
	m_fSoul -= m_fDecreaseSpd * fDT;

	if (m_fTimer > P_FOCUSMAX)
	{
		info.uiHP++;
		if (KEY_HOLD('A'))
			changeMyState(getOwner(), eSTATE_PLAYER::FOCUS);
		else
			changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}

	if (m_fSoul < 0.f)
	{
		m_fSoul = 0.f;
		changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}

	info.uiSoul = (UINT)m_fSoul;
	getPlayer()->setPlayerInfo(info);
}

void CState_Focus::enter()
{
	m_fSoul = (float)(getPlayer()->getPlayerInfo().uiSoul);
	getPlayer()->playAnim(L"Focus");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Focus::exit()
{
	m_fTimer = 0.f;
	m_fSoul = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);
}

void CState_Focus::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Focus";

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	//TODO
}
