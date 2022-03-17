#include "framework.h"
#include "CAttack.h"

CAttack::CAttack()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::ATTACK);

	m_eDir = eDIR::NONE;
	m_fDura = 0.1f;
	m_uiDmg = 1;

	createCollider();
	getCollider()->setSize(fPoint(0.f,0.f));
	getCollider()->setShape(eSHAPE::RECT);
}

CAttack::~CAttack()
{
}

CAttack* CAttack::clone()
{
	return new CAttack(*this);
}

void CAttack::update()
{
	m_fDura -= fDT;

	if (m_fDura < 0.f)
		deleteObj(this);
}

void CAttack::render(HDC hDC)
{


	componentRender(hDC);
}

void CAttack::setDir(eDIR dir)
{
	m_eDir = dir;
}

void CAttack::setDura(float dura)
{
	m_fDura = dura;
}

void CAttack::setDmg(UINT dmg)
{
	m_uiDmg = dmg;
}


void CAttack::collisionEnter(CCollider* pOther)
{

}
