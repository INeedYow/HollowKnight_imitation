#include "framework.h"
#include "CState_Fly_Move.h"
#include "CMonster.h"
#include "CPlayer.h"

CState_Fly_Move::CState_Fly_Move(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
}

CState_Fly_Move::~CState_Fly_Move()
{
}

void CState_Fly_Move::update(UINT& chk)
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
		changeMonsState(getOwner(), eSTATE_MONS::FLY_IDLE);
	}

	pos.x += info.fvDir.x * info.fSpdX * fDT;
	pos.y -= info.fvDir.y * info.fSpdY * fDT;


	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Fly_Move::enter()
{
	m_fTimer = (float)((rand() % 4 + 2) * 0.5f);

	tMonsInfo info = getMonster()->getMonsInfo();

	info.fvDir.x = (float)(rand() % 2);			// ÁÂ¿ì ·£´ý
	if (!info.fvDir.x)
		info.fvDir.x = -1;

	info.fvDir.y = (float)(rand() % 3 - 1);			// »óÇÏ ·£´ý

	info.fvDir.normalize();

	getMonster()->setMonsInfo(info);
}

void CState_Fly_Move::exit()
{
	m_fTimer = 0.f;
}

void CState_Fly_Move::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Fly_Move";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}