#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"

CMonster* CMonster::clone()
{
	return new CMonster(*this);
}

CMonster::CMonster()
{
	m_fpCenterPos = fPoint(0, 0);
	m_fSpeed = 0;
	m_fDistance = 300;
	m_bUpDir = true;

	setName(OBJNAME::MONSTER);
	setSize(fPoint(100.f, 100.f));

	createCollider();
	getCollider()->setSize(fPoint(90.f, 90.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	fPoint pos = getPos();

	if (m_bUpDir)
	{
		pos.y -= fDT * m_fSpeed;
		if (pos.y < m_fpCenterPos.y - m_fDistance)
			m_bUpDir = false;
	}
	else
	{
		pos.y += fDT * m_fSpeed;
		if (pos.y > m_fpCenterPos.y + m_fDistance)
			m_bUpDir = true;
	}

	setPos(pos);
}

void CMonster::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint size = getSize();
	Rectangle(hDC,
		(int)(pos.x - size.x / 2),
		(int)(pos.y - size.y / 2),
		(int)(pos.x + size.x / 2),
		(int)(pos.y + size.y / 2) );
}

void CMonster::setCenterPos(fPoint point)
{
	m_fpCenterPos = point;
}

void CMonster::collisionEnter(CCollider* pOther)
{

}