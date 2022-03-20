#include "framework.h"
#include "CAttack.h"
#include "CPlayer.h"

CAttack::CAttack()
{
	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::ATTACK);

	m_pOwner = nullptr;
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

void CAttack::setOwner(CObject* pOwner)
{
	m_pOwner = pOwner;
}

CObject* CAttack::getOwner()
{
	return m_pOwner;
}


void CAttack::collisionEnter(CCollider* pOther)
{
	CObject* pOwner = getOwner();
	CObject* pTarget = pOther->getOwner();

	if (eOBJNAME::PLAYER == pOwner->getName())
	{
		tPlayerInfo info = ((CPlayer*)pOwner)->getPlayerInfo();

		switch (pTarget->getName())
		{
		case eOBJNAME::BOSS:
		{
			info.fvKnockBackDir = (pOwner->getPos() - pTarget->getPos());
			info.uiSoul += 10;
			break;
		}
		}
		
		((CPlayer*)pOwner)->setPlayerInfo(info);
	}
}
