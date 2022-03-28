#include "framework.h"
#include "CState_Death.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Death::CState_Death(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fDura = 0.f;
}

CState_Death::~CState_Death()
{
}

void CState_Death::update(UINT& chk)
{
	m_fDura -= fDT;

	// TODO
	if (m_fDura < 0.f)
	{
		if (chk & SP_AIR)
			changeMyState(getOwner(), eSTATE_PLAYER::FALL);
		else
			changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}
}

void CState_Death::enter()
{
	m_fDura = 2.4f;
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_NODMG, true);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fNoDmgTimer = 1.5f + m_fDura;
	getPlayer()->setPlayerInfo(info);

	getPlayer()->playAnim(L"Death");

	CSoundManager::getInst()->addSound(L"hero_death", L"sound\\player\\hero_death_extra_details.wav");
	CSoundManager::getInst()->play(L"hero_death", 0.2f);
}

void CState_Death::exit()
{
	m_fDura = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);

	// юс╫ц
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.uiHP = 5;
	info.uiSoul = 100;
	getPlayer()->setPlayerInfo(info);
}

void CState_Death::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Death";
	wchar_t bufDura[255] = {};

	swprintf_s(bufDura, L"dura = %.1f", m_fDura);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDura, (int)wcslen(bufDura));
}
