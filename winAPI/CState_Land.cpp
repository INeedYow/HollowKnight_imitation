#include "framework.h"
#include "CState_Land.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Land::CState_Land(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fDura = 0.f;
}

CState_Land::~CState_Land()
{
}

void CState_Land::update(UINT& chk)
{
	m_fDura -= fDT;
	if (m_fDura <= 0.4f)
	{
		getPlayer()->playAnim(L"Land2Idle");

		if (m_fDura < 0.f)
			changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}
}

void CState_Land::enter()
{
	m_fDura = 1.5f;
	getPlayer()->playAnim(L"Land");

	CSoundManager::getInst()->addSound(L"hero_land_hard", L"sound\\player\\hero_land_hard.wav");
	CSoundManager::getInst()->play(L"hero_land_hard", 0.1f);
}

void CState_Land::exit()
{
	m_fDura = 0.f;
}

void CState_Land::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Land";
	wchar_t bufDura[255] = {};

	swprintf_s(bufDura, L"dura = %.1f", m_fDura);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDura, (int)wcslen(bufDura));
}
