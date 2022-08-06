#include "framework.h"
#include "CState_Stand.h"
#include "CMonster.h"
#include "CPlayer.h"

CState_Stand::CState_Stand(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
}

CState_Stand::~CState_Stand()
{
}

void CState_Stand::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	fPoint size = getMonster()->getSize();
	tMonsInfo info = getMonster()->getMonsInfo();

	getMonster()->playAnim(L"Stand");

	if (info.fDist <= info.fNoticeRange)
	{
		if (playerPos.y >= pos.y - size.y * 0.6f &&
			playerPos.y <= pos.y + size.y * 0.6f)
		{
			changeMonsState(getOwner(), eSTATE_MONS::TRACE);
		}
	}

	m_fTimer -= fDT;
	if (m_fTimer < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::PATROL);
	}

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Stand::enter()
{
	m_fTimer = (float)((rand() % 6 + 1) * 0.5f);
}

void CState_Stand::exit()
{
	m_fTimer = 0.f;
}

void CState_Stand::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Stand";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}