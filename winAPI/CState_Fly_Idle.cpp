#include "framework.h"
#include "CState_Fly_Idle.h"
#include "CMonster.h"
#include "CPlayer.h"

CState_Fly_Idle::CState_Fly_Idle(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
}

CState_Fly_Idle::~CState_Fly_Idle()
{
}

void CState_Fly_Idle::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	fPoint size = getMonster()->getSize();
	tMonsInfo info = getMonster()->getMonsInfo();

	getMonster()->playAnim(L"Fly");

	if (info.fDist <= info.fAtkRange)
	{
		changeMonsState(getOwner(), eSTATE_MONS::SHOOT);
	}

	m_fTimer -= fDT;
	if (m_fTimer < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::FLY_MOVE);
	}

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Fly_Idle::enter()
{
	m_fTimer = (float)((rand() % 4 + 2) * 0.5f);
}

void CState_Fly_Idle::exit()
{
	m_fTimer = 0.f;
}

void CState_Fly_Idle::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Fly_Idle";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}