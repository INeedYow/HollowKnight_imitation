#include "framework.h"
#include "CState_Patrol.h"
#include "CMonster.h"
#include "CPlayer.h"

CState_Patrol::CState_Patrol(eSTATE_MONS state)
	:CState_Mons(state) 
{
	m_fTimer = 0.f;
}

CState_Patrol::~CState_Patrol()
{
}

void CState_Patrol::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	fPoint size = getMonster()->getSize();
	tMonsInfo info = getMonster()->getMonsInfo();

	if (chk & SM_TRACE)
	{
		if (pos.y - size.y / 2.f < playerPos.y &&
			playerPos.y < pos.y + size.y / 2.f)
		{
			if (info.fDist < info.fTraceRange)
			{
				changeMonsState(getOwner(), eSTATE_MONS::TRACE);
			}
		}
	}

	m_fTimer -= fDT;
	if (m_fTimer < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}

	pos.x += info.fvDir.x * info.fSpd * fDT;

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Patrol::enter()
{
	m_fTimer = 3.5f;

	tMonsInfo info = getMonster()->getMonsInfo();

	info.fvDir.x = (float)(rand() % 2);			// �¿� ����
	if (!info.fvDir.x)
		info.fvDir.x = -1;
	
	getMonster()->setMonsInfo(info);

	getMonster()->playAnim(L"BT_Patrol");
}

void CState_Patrol::exit()
{
	m_fTimer = 0.f;
}

void CState_Patrol::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Patrol";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 65, strInfo, (int)wcslen(strInfo));
}