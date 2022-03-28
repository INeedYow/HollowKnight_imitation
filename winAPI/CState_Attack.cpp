#include "framework.h"
#include "CState_Attack.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CAI.h"

CState_Attack::CState_Attack(eSTATE_MONS state)
	:CState_Mons(state) 
{
}

CState_Attack::~CState_Attack()
{
}

void CState_Attack::update(UINT& chk)
{
	//TODO
}

void CState_Attack::enter()
{
}

void CState_Attack::exit()
{
}

void CState_Attack::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Attack";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}
