#include "framework.h"
#include "CState_Trace.h"
#include "CMonster.h"
#include "CPlayer.h"

// TODO 생성자 재정의 해서 상태 변수값 받으면 어떤가
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
	fPoint playerPos = gameGetPlayer()->getPos();
	fPoint size = getMonster()->getSize();
	tMonsInfo info = getMonster()->getMonsInfo();

	if (playerPos.y < pos.y - size.y ||
		playerPos.y > pos.y + size.y / 2.f||
		info.fDist > info.fTraceRange)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}

	pos.x += info.fvDir.x * info.fSpd * fDT;

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Trace::enter()
{
	tMonsInfo info = getMonster()->getMonsInfo();
	
	info.fvDir.x = gameGetPlayer()->getPos().x - getMonster()->getPos().x;

	getMonster()->setMonsInfo(info);

	getMonster()->playAnim(L"BT_Trace");
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
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 65, strInfo, (int)wcslen(strInfo));
}

