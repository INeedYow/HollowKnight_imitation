#include "framework.h"
#include "CMonster_Melee.h"
#include "CAttack.h"

CMonster_Melee::CMonster_Melee()
{
	m_iBottomCnt = 0;
}

CMonster_Melee::~CMonster_Melee()
{
}

CMonster_Melee* CMonster_Melee::clone()
{
	return nullptr;
}

void CMonster_Melee::update()
{
	CMonster::update();
}

void CMonster_Melee::render(HDC hDC)
{
	componentRender(hDC);
}

void CMonster_Melee::collisionEnter(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();

	switch (pTarget->getName())
	{
	case eOBJNAME::ATTACK:
	{	// attck의 오너가 플레이어일 때
		if (eOBJNAME::PLAYER == ((CAttack*)pTarget)->getOwner()->getName())
		{
			tMonsInfo info = getMonsInfo();
			info.iHP--;
			setMonsInfo(info);
		}
		break;
	}
	case eOBJNAME::MISSILE_PLAYER:
	{
		tMonsInfo info = getMonsInfo();
		info.iHP -= 2;
		setMonsInfo(info);
		break;
	}

	}
}

void CMonster_Melee::collisionKeep(CCollider* pOther)
{
}

void CMonster_Melee::collisionExit(CCollider* pOther)
{
}

void CMonster_Melee::death()
{

}