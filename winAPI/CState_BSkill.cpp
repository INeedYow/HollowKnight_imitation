#include "framework.h"
#include "CState_BSkill.h"
#include "CMonster.h"
#include "CShield.h"
#include "CBoss_Markoth.h"
#include "SelectGDI.h"

CState_BSkill::CState_BSkill(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fDura = 0.f;
	m_fRad = 0.f;
	m_fSpd = 0.f;
}

CState_BSkill::~CState_BSkill()
{
}

void CState_BSkill::update(UINT& chk)
{
	vector<CShield*> vecShd = ((CBoss_Markoth*)getMonster())->getVecShield();

	m_fDura -= fDT;

	if (m_fDura >= (float)B_SKILL_DURA / 2.f)
	{	// ���� 2�� �̻��� �� 1���� �������� ����
		int i = vecShd.size() >= 2 ? 1 : 0;

		for (; i < vecShd.size(); i++)
		{	// ���� ����
			vecShd[i]->setRadius(vecShd[i]->getRadius() + 150.f * fDT);
		}
	}
	else
	{
		int i = vecShd.size() >= 2 ? 1 : 0;

		for (; i < vecShd.size(); i++)
		{	// ���� ����
			vecShd[i]->setRadius(vecShd[i]->getRadius() - 150.f * fDT);
		}
	}

	if (m_fDura < 0.f)
	{
		m_fDura = 0.f;

		for (int i = 0; i < vecShd.size(); i++)
		{
			vecShd[i]->setfSpeed(vecShd[i]->getSpeed() - 1.8f * fDT);

			if (vecShd[i]->getSpeed() <= 1.8f)
				changeMonsState(getOwner(), eSTATE_MONS::SPAWN);
		}

		/*if (vecShd[0]->getSpeed() <= 0.f)
		{
			for (int i = 0; i < vecShd.size(); i++)
			{
				vecShd[i]->setfSpeed((float)SB_SHIELD_SPD);
				vecShd[i]->setRadius((float)SB_SHIELD_RAD);
			}
		}*/
		/*changeMonsState(getOwner(), eSTATE_MONS::SPAWN);*/
	}

	m_fSpd = vecShd[vecShd.size() - 1]->getSpeed();
	m_fRad = vecShd[vecShd.size() - 1]->getRadius();
}

void CState_BSkill::enter()
{
	m_fDura = (float)B_SKILL_DURA;
	getMonster()->PLAY(L"st_Skill");
	getMonster()->getCollider()->setSize(fPoint(SB_SkSIZEX, SB_SkSIZEY));
}

void CState_BSkill::exit()
{
	getMonster()->setCheck(SB_TIMER, true);
	((CBoss_Markoth*)getMonster())->setSkillCooldown((float)B_SKILL_COOL);
}

void CState_BSkill::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strState = L"Skill";
	wchar_t bufDura[255] = {};
	wchar_t bufSpd[255] = {};
	wchar_t bufRad[255] = {};

	swprintf_s(bufDura, L"Dura %.1f", m_fDura);
	swprintf_s(bufSpd, L"ShieldSpd = %.1f", m_fSpd);
	swprintf_s(bufRad, L"ShieldRad = %.1f", m_fRad);

	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 125, strState, (int)wcslen(strState));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 145, bufDura, (int)wcslen(bufDura));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 165, bufSpd, (int)wcslen(bufSpd));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 185, bufRad, (int)wcslen(bufRad));
}
