#include "framework.h"
#include "CState_Shoot.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CAI.h"
#include "CMonster_Fly.h"

CState_Shoot::CState_Shoot(eSTATE_MONS state)
	:CState_Mons(state) 
{
	m_fDura = 0.f;
}

CState_Shoot::~CState_Shoot()
{
}

void CState_Shoot::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();

	m_fDura -= fDT;

	if (m_fDura <= 0.f || info.fDist > M_BE_ATT_RNG)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}

}

void CState_Shoot::enter()
{
	getMonster()->playAnim(L"Shoot");
	m_fDura = 2.4f;
}

void CState_Shoot::exit()
{
	m_fDura = 0.f;
}

void CState_Shoot::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Shoot";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}
