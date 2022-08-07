#include "framework.h"
#include "CState_BIdle.h"
#include "CMonster.h"
#include "CBoss_Markoth.h"
#include "SelectGDI.h"

CState_BIdle::CState_BIdle(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fDura = 0;;
}

CState_BIdle::~CState_BIdle()
{
}

void CState_BIdle::update(UINT& chk)
{
	m_fDura -= fDT;

	if (m_fDura < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::B_MOVE);
	}
}

void CState_BIdle::enter()
{
	m_fDura = (float)(rand() % 3  + 4) * 0.5f;
	getMonster()->PLAY(L"st_Normal");
	getMonster()->getCollider()->setSize(fPoint(SB_NmSIZEX, SB_NmSIZEY));
}

void CState_BIdle::exit()
{
}

void CState_BIdle::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strState = L"Idle";
	wchar_t bufDura[255] = {};
	swprintf_s(bufDura, L"Dura %.1f", m_fDura);
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 125, strState, (int)wcslen(strState));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 145, bufDura, (int)wcslen(bufDura));
}
