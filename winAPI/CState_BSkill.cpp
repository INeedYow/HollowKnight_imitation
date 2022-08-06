#include "framework.h"
#include "CState_BSkill.h"
#include "CMonster.h"
#include "CShield.h"
#include "CBoss_Markoth.h"
#include "SelectGDI.h"
#include "CSpear.h"


CState_BSkill::CState_BSkill(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fDura = 0.f;
}

CState_BSkill::~CState_BSkill()
{
}

void CState_BSkill::update(UINT& chk)
{

	m_fDura -= fDT;

	if (m_fDura >= (float)B_SKILL_DURA * 0.5f)
	{	// ���� 2�� �̻��� �� 1���� �������� ����
		int i = m_vecShields.size() >= 2 ? 1 : 0;

		for (; i < m_vecShields.size(); i++)
		{	// ���� ����
			m_vecShields[i]->setRadius(m_vecShields[i]->getRadius() + B_SKILL_RAD * fDT);
		}
	}
	else
	{
		int i = m_vecShields.size() >= 2 ? 1 : 0;

		for (; i < m_vecShields.size(); i++)
		{	// ���� ����
			m_vecShields[i]->setRadius(m_vecShields[i]->getRadius() - B_SKILL_RAD * fDT);
		}
	}

	if (m_fDura < 0.f)
	{
		for (int i = 0; i < m_vecShields.size(); i++)
		{	// �ӵ�, ���� �������
			m_vecShields[i]->setfSpeed((float)B_SHD_SPD);
			m_vecShields[i]->setRadius((float)B_SHD_RAD);
		}

		changeMonsState(getOwner(), eSTATE_MONS::B_IDLE);
	}
}

void CState_BSkill::enter()
{
	m_fDura = (float)B_SKILL_DURA;
	getMonster()->setCheck(SB_TIMER, false);

	vector<CSpear*> vecSpr = ((CBoss_Markoth*)getMonster())->getVecSpear();
	{	// ��ų ���� ���� ��Ȱ��ȭ
		for (int i = 0; i < vecSpr.size(); i++)
		{
			vecSpr[i]->setActive(false);
		}
	}

	m_vecShields = ((CBoss_Markoth*)getMonster())->getVecShield();
}

void CState_BSkill::exit()
{
	getMonster()->setCheck(SB_TIMER, true);
	((CBoss_Markoth*)getMonster())->setSkillCooldown((float)B_SKILL_COOL);

	((CBoss_Markoth*)getMonster())->setSpawnTimer(0.75f);
}

void CState_BSkill::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strState = L"Skill";
	wchar_t bufDura[255] = {};
	//wchar_t bufSpd[255] = {};
	//wchar_t bufRad[255] = {};

	swprintf_s(bufDura, L"Dura %.1f", m_fDura);
	//swprintf_s(bufSpd, L"ShieldSpd = %.1f", m_fSpd);
	//swprintf_s(bufRad, L"ShieldRad = %.1f", m_fRad);

	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 125, strState, (int)wcslen(strState));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 145, bufDura, (int)wcslen(bufDura));
	/*TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 165, bufSpd, (int)wcslen(bufSpd));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 185, bufRad, (int)wcslen(bufRad));*/
}
