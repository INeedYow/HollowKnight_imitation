#include "framework.h"
#include "CState_BReady.h"
#include "CMonster.h"
#include "CShield.h"
#include "CBoss_Markoth.h"
#include "SelectGDI.h"

CState_BReady::CState_BReady(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fDura = 0.f;
	m_fSpd = 0.f;
}

CState_BReady::~CState_BReady()
{
}

void CState_BReady::update(UINT& chk)
{
	vector<CShield*> vecShd = ((CBoss_Markoth*)getMonster())->getVecShield();

	m_fDura -= fDT;

	if (m_fDura > B_READY_DURA - 0.75f)
	{	// 방패 감속
		for (int i = 0; i < vecShd.size(); i++)
		{
			vecShd[i]->setfSpeed(vecShd[i]->getSpeed() - (float)B_ACCEL * fDT);
		}
	}
	else if (B_READY_DURA - 0.75f >= m_fDura && m_fDura > B_READY_DURA - 1.f)	// 단계에 대한 변수를 시간으로 대신 함
	{	// 방향 전환
		for (int i = 0; i < vecShd.size(); i++)
		{
			vecShd[i]->toggleRot();
		}
		getMonster()->PLAY(L"st_Skill");
		getMonster()->getCollider()->setSize(fPoint(SB_SkSIZEX, SB_SkSIZEY));
		m_fDura = B_READY_DURA - 1.25f;
	}
	else if (B_READY_DURA - 1.25f >= m_fDura && m_fDura > 0.f)
	{	// 방패 가속
		for (int i = 0; i < vecShd.size(); i++)
		{
			vecShd[i]->setfSpeed(vecShd[i]->getSpeed() + (float)B_ACCEL * fDT);
		}
	}
	else
	{	// 스킬 시작
		changeMonsState(getOwner(), eSTATE_MONS::SKILL);
	}

	m_fSpd = vecShd[vecShd.size() - 1]->getSpeed();
}

void CState_BReady::enter()
{
	m_fDura = B_READY_DURA;
	m_fSpd = 0.f;
	getMonster()->PLAY(L"st_Middle");
	getMonster()->setCheck(SB_TIMER, false);
	getMonster()->getCollider()->setSize(fPoint(SB_MdSIZEX, SB_MdSIZEY));

	if (rand() % 2)
	{
		CSoundManager::getInst()->addSound(L"markoth_cast2", L"sound\\boss\\Markoth_cast_02.wav");
		CSoundManager::getInst()->play(L"markoth_cast2", 0.1f);
	}
	else
	{
		CSoundManager::getInst()->addSound(L"markoth_cast3", L"sound\\boss\\Markoth_cast_03.wav");
		CSoundManager::getInst()->play(L"markoth_cast3", 0.1f);
	}
}

void CState_BReady::exit()
{
}

void CState_BReady::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strState = L"Ready";
	wchar_t bufDura[255] = {};
	//wchar_t bufSpd[255] = {};

	swprintf_s(bufDura, L"Dura %.1f", m_fDura);
	//swprintf_s(bufSpd, L"ShieldSpd = %.1f", m_fSpd);

	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 125, strState, (int)wcslen(strState));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 145, bufDura, (int)wcslen(bufDura));
	//TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 165, bufSpd, (int)wcslen(bufSpd));
}
