#include "framework.h"
#include "CState_Trace.h"
#include "CMonster.h"

// TODO 생성자 재정의 해서 상태 변수값 받으면 .
CState_Trace::CState_Trace(eSTATE_MONS state)
	:CState_Mons(state)
{
}

CState_Trace::~CState_Trace()
{
}

void CState_Trace::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();

	if (info.fDist > info.fTraceRange)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}

	if (info.fAtkRange <= info.fDist)
	{
		changeMonsState(getOwner(), eSTATE_MONS::ATTACK);
	}

	if (chk & SM_AIR)
	{
		// TODO
	}

	pos.x += info.fvDir.x * info.fSpd * fDT;

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Trace::enter()
{
	tMonsInfo info = getMonster()->getMonsInfo();
	
	info.fvDir.x = getMyPos().x - getMonster()->getPos().x;

	getMonster()->setMonsInfo(info);
}

void CState_Trace::exit()
{
}

void CState_Trace::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Trace";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 125, strInfo, (int)wcslen(strInfo));
}

