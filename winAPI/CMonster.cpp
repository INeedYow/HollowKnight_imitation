#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CAI.h"

CMonster::CMonster()
{
	m_uiCheck = 0;
	m_iHP = 1;
	m_fSpd = 10.f;

	setName(eOBJNAME::MONSTER);
	setSize(fPoint(100.f, 100.f));

	createCollider();
}

CMonster::~CMonster()
{
}

void CMonster::setCheck(UINT chk, bool isOn)
{
	if (isOn)
		m_uiCheck |= chk;
	else
		m_uiCheck &= ~(chk);
}

void CMonster::setHP(int hp)
{
	m_iHP = hp;
}

void CMonster::setSpd(float spd)
{
	m_fSpd = spd;
}

bool CMonster::isCheck(UINT chk)
{
	return m_uiCheck & chk;
}

UINT CMonster::getHP()
{
	return m_iHP;
}

float CMonster::getSpd()
{
	return m_fSpd;
}
