#include "framework.h"
#include "CState_BSpawn.h"
#include "CMonster.h"
#include "CBoss_Markoth.h"
#include "SelectGDI.h"

CState_BSpawn::CState_BSpawn(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fDura = 0;
	m_bSpawn = false;
}

CState_BSpawn::~CState_BSpawn()
{
}

void CState_BSpawn::update(UINT& chk)
{
	m_fDura -= fDT;

	if (m_fDura < 0.4f)
	{
		getMonster()->PLAY(L"st_Skill");

		if (!m_bSpawn)
		{
			((CBoss_Markoth*)getMonster())->spawnShield();
			((CBoss_Markoth*)getMonster())->createSpear();
			m_bSpawn = true;
		}
	
	}

	if (m_fDura < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::IDLE);
		getMonster()->getCollider()->setSize(fPoint(SB_NmSIZEX, SB_NmSIZEY));
	}
}

void CState_BSpawn::enter()
{
	m_fDura = 0.9f;
	m_bSpawn = false;
	getMonster()->PLAY(L"st_Middle");
	getMonster()->getCollider()->setSize(fPoint(SB_MdSIZEX, SB_MdSIZEY));
}

void CState_BSpawn::exit()
{
	m_fDura = 0.f;
	m_bSpawn = false;
}

void CState_BSpawn::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strState = L"Spawn";
	wchar_t bufDura[255] = {};
	swprintf_s(bufDura, L"Dura %.1f", m_fDura);
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 125, strState, (int)wcslen(strState));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 145, bufDura, (int)wcslen(bufDura));
}
