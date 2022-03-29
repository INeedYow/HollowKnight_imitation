#include "framework.h"
#include "CState_BDeath.h"
#include "CEffect.h"
#include "CBoss_Markoth.h"

#include "SelectGDI.h"

CState_BDeath::CState_BDeath(eSTATE_MONS state)
	:CState_Mons(state) 
{
	m_fDura = 0.f;
}

CState_BDeath::~CState_BDeath()
{
}

void CState_BDeath::update(UINT& chk)
{
	m_fDura -= fDT;

	if (m_fDura < 0.f)
	{
		deleteObj(getMonster());
	}
}

void CState_BDeath::enter()
{
	getMonster()->PLAY(L"st_Skill");
	m_fDura = 4.f;
}

void CState_BDeath::exit()
{
}

void CState_BDeath::printInfo(HDC hDC)
{
}
