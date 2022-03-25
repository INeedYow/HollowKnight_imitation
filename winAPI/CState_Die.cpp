#include "framework.h"
#include "CState_Die.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CAI.h"

CState_Die::CState_Die(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
}

CState_Die::~CState_Die()
{
}

void CState_Die::update(UINT& chk)
{
	m_fTimer -= fDT;

	if (m_fTimer < 0.f)
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
}

void CState_Die::enter()
{
	m_fTimer = 2.4f;
	
	getMonster()->playAnim(L"Die");
}

void CState_Die::exit()
{
	deleteObj(getMonster());
}

void CState_Die::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Die";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 65, strInfo, (int)wcslen(strInfo));
	
	wchar_t bufTimer[255] = {};
	swprintf_s(bufTimer, L"%.1fs", m_fTimer);
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 35, bufTimer, (int)wcslen(bufTimer));
}
