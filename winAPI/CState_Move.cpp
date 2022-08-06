#include "framework.h"
#include "CState_Move.h"
#include "CMonster.h"
#include "CPlayer.h"

CState_Move::CState_Move(eSTATE_MONS state)
	:CState_Mons(state)
{
}

CState_Move::~CState_Move()
{
}

void CState_Move::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();

	getMonster()->playAnim(L"Move");

	pos.x += info.fvDir.x * info.fSpdX * fDT;

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Move::enter()
{
}

void CState_Move::exit()
{
}

void CState_Move::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Move";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}