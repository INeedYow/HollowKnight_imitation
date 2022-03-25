#include "framework.h"
#include "CState_Stop.h"
#include "CMonster.h"
#include "CPlayer.h"

CState_Stop::CState_Stop(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
}

CState_Stop::~CState_Stop()
{
}

void CState_Stop::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	fPoint size = getMonster()->getSize();
	tMonsInfo info = getMonster()->getMonsInfo();

	if (chk & SM_TRACE)
	{
		if (info.fDist <= info.fTraceRange)
		{
			if (playerPos.y >= pos.y - size.y &&
				playerPos.y <= pos.y + size.y / 2.f)
			{
				changeMonsState(getOwner(), eSTATE_MONS::TRACE);
			}
		}
	}

	m_fTimer -= fDT;

	if (m_fTimer < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::PATROL);
	}
}

void CState_Stop::enter()
{
	m_fTimer = 2.f;
	getMonster()->playAnim(L"BT_Stop");
}

void CState_Stop::exit()
{
	m_fTimer = 0.f;
}

void CState_Stop::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Stop";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 65, strInfo, (int)wcslen(strInfo));
}
