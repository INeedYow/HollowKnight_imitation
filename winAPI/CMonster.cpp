#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CAI.h"

CMonster::CMonster()
{
	m_uiState = 0;
	m_uiHP = 1;
	m_fSpd = 10.f;

	setName(eOBJNAME::MONSTER);
	setSize(fPoint(100.f, 100.f));

	createCollider();
}

CMonster::~CMonster()
{
}

void CMonster::setAI(CAI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::setState(UINT state, bool isOn)
{
	if (isOn)
		m_uiState |= state;
	else
		m_uiState &= ~(state);
}

void CMonster::setHP(UINT hp)
{
	m_uiHP = hp;
}

void CMonster::setSpd(float spd)
{
	m_fSpd = spd;
}

bool CMonster::isState(UINT state)
{
	return m_uiState & state;
}

UINT CMonster::getHP()
{
	return m_uiHP;
}

float CMonster::getSpd()
{
	return m_fSpd;
}
