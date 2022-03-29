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
		CSoundManager::getInst()->addSound(L"focus_health_heal", L"sound\\player\\focus_health_heal.wav");
		CSoundManager::getInst()->play(L"focus_health_heal", 0.2f);
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
	CSoundManager::getInst()->addSound(L"hero_focus_prepare", L"sound\\player\\hero_nail_art_charge_initiate.wav");
	CSoundManager::getInst()->play(L"hero_focus_prepare", 0.1f);

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
	wchar_t bufTime[255] = {};
	wchar_t bufMax[255] = {};

	swprintf_s(bufTime, L"SpdY = %.1f", m_fTimer);
	swprintf_s(bufMax, L"Max = %.1f", (float)P_FOCUSMAX);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufTime, (int)wcslen(bufTime));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 100, bufMax, (int)wcslen(bufMax));

}
