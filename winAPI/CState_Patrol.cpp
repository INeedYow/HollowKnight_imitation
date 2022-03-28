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

	getMonster()->playAnim(L"Patrol");

	if (chk & SM_TRACE)
	{
		if (info.fDist <= info.fNoticeRange)
		{
			if (playerPos.y >= pos.y - size.y &&
				playerPos.y <= pos.y + size.y / 2.f)
			{
				changeMonsState(getOwner(), eSTATE_MONS::TRACE);
			}
		}
	}

	if (chk & SM_SHOOT)
	{
		if (info.fDist <= info.fAtkRange)
		{
			changeMonsState(getOwner(), eSTATE_MONS::SHOOT);
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
	m_fTimer = (float)((rand() % 6 + 1) / 2.f);

	tMonsInfo info = getMonster()->getMonsInfo();

	info.fvDir.x = (float)(rand() % 2);			// �¿� ����
	if (!info.fvDir.x)
		info.fvDir.x = -1;

	// TODO

	//if (getMonster()->isCheck(SM_FLY))
	//{
	//	switch (rand() % 3)
	//	{
	//	case 0:

	//	}
	//}
	
	getMonster()->setMonsInfo(info);
}

void CState_Patrol::exit()
{
	m_fTimer = 0.f;
}

void CState_Patrol::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Patrol";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}