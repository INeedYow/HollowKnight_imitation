#include "framework.h"
#include "CMissile.h"
#include "CCollider.h"

CMissile* CMissile::clone()
{
	return new CMissile(*this);
}

CMissile::CMissile()
{
	setSize(fPoint(25.f, 25.f));
	setName(eOBJNAME::MISSILE_MONSTER);
	m_fvDir = fVec2(0, 0);
	m_fSpeed = 0.f;
	m_fTimer = 0.f;

	createCollider();
	getCollider()->setSize(fPoint(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	fPoint pos = getPos();

	pos.x += m_fSpeed * m_fvDir.x * fDT;
	pos.y += m_fSpeed * m_fvDir.y * fDT;

	m_fTimer += fDT;

	if (m_fTimer > 8.f)
		deleteObj(this);

	setPos(pos);
}

void CMissile::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint scale = getSize();

	fPoint fptRenderPos = rendPos(pos);

	Ellipse(hDC,
		(int)(fptRenderPos.x - scale.x / 2.f),
		(int)(fptRenderPos.y - scale.y / 2.f),
		(int)(fptRenderPos.x + scale.x / 2.f),
		(int)(fptRenderPos.y + scale.y / 2.f));

	componentRender(hDC);
}

void CMissile::setDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CMissile::setDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CMissile::setSpeed(float spd)
{
	m_fSpeed = spd;
}

float CMissile::getSpeed()
{
	return m_fSpeed;
}

void CMissile::collisionEnter(CCollider* pOther)
{
	CObject* pOtherObj = pOther->getOwner();

	if (eOBJNAME::MISSILE_PLAYER == getName())
	{	// 플레이어 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::MONSTER:
		case eOBJNAME::BOSS:
		case eOBJNAME::TILE:
		{
			//deleteObj(this);
			// TODO 이펙트 생성
			break;
		}

		}
	}
	else if (eOBJNAME::MISSILE_MONSTER == getName())
	{	// 몬스터의 미사일인 경우
		switch (pOther->getOwner()->getName())
		{
		case eOBJNAME::PLAYER:
		case eOBJNAME::TILE:
		{
			deleteObj(this);
			// TODO 이펙트 생성
			break;
		}

		}
	}
}
