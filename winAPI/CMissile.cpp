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
	m_fvDir = fVec2(0, 0);
	m_fSpeed = 400.f;
	setName(OBJNAME::MISSILE_PLAYER);

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

	setPos(pos);

	if (pos.x < 0 || pos.x > WINSIZEX
		|| pos.y < 0 || pos.y > WINSIZEY)
		deleteObj(this);
}

void CMissile::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint scale = getSize();

	fPoint fptRenderPos = getRendPos(pos);

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

void CMissile::collisionEnter(CCollider* pOther)
{
	CObject* pOtherObj = pOther->getOwner();
	if (pOtherObj->getName() == OBJNAME::MONSTER)
	{
		deleteObj(this);
	}
}
