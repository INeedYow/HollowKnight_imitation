#include "framework.h"
#include "CState_Patrol.h"
#include "CMonster.h"

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
	tMonsInfo info = getMonster()->getMonsInfo();

	if (info.fDist > info.fTraceRange)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}

	if (chk & SM_AIR)
	{
		// TODO
	}

	pos.x += info.fvDir.x * info.fSpd * fDT;

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Patrol::enter()
{
	m_fTimer = 3.f;

	tMonsInfo info = getMonster()->getMonsInfo();

	info.fvDir.x = (float)(rand() % 2);			// ÁÂ¿ì ·£´ý
	if (!info.fvDir.x)
		info.fvDir.x = -1;
	
	getMonster()->setMonsInfo(info);
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

	LPCWSTR	strInfo = L"Trace";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 125, strInfo, (int)wcslen(strInfo));
}
