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
	tMonsInfo info = getMonster()->getMonsInfo();

	if (info.fDist > info.fTraceRange)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}
}

void CState_Trace::enter()
{
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
}
