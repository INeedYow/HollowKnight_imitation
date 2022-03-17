#include "framework.h"
#include "CTest.h"

CTest* CTest::clone()
{
	return new CTest(*this);
}

CTest::CTest()
{
	setPos(fPoint (0.f, 0.f));
	setSize(fPoint(50.f, 50.f));
	m_fvDir = fVec2(0, 0);
	m_fSpeed = 400.f;
	m_fTimer = 0.f;
	m_fTheta = 0.f;
	setName(eOBJNAME::TEST);
	m_pOwner = nullptr;

	m_fpOffset = {};

	createCollider();
	getCollider()->setSize(fPoint(15.f, 15.f));
}

CTest::~CTest()
{
}

void CTest::update()
{
	m_fTheta += 5 * fDT;

	m_fTimer += fDT;

	if (m_fTimer < 4.f)
		m_fSpeed += 350 * fDT;
	else
		m_fSpeed -= 350 * fDT;

	setDir(m_fTheta);

	if (m_bRotRight)
	{
		m_fpOffset.x += m_fSpeed * m_fvDir.x * fDT;
		m_fpOffset.y += m_fSpeed * m_fvDir.y * fDT;
	}
	else
	{
		m_fpOffset.x -= m_fSpeed * m_fvDir.x * fDT;
		m_fpOffset.y -= m_fSpeed * m_fvDir.y * fDT;
	}

	if (m_fTimer > 8.f)
		deleteObj(this);

	fPoint ownerPos = m_pOwner->getPos();
	fPoint pos = ownerPos + m_fpOffset;
	
	setPos(pos);
}

void CTest::render(HDC hDC)
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

void CTest::setDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CTest::setDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CTest::setRot(bool isRight)
{
	m_bRotRight = isRight;
}

void CTest::setOwner(CObject* pOwner)
{
	m_pOwner = pOwner;
}

void CTest::setOffset(fPoint offset)
{
	m_fpOffset = offset;
}

void CTest::collisionEnter(CCollider* pOther)
{
	//CObject* pOtherObj = pOther->getOwner();

	//if (OBJNAME::MISSILE_PLAYER == getName())
	//{	// 플레이어 미사일인 경우
	//	switch (pOther->getOwner()->getName())
	//	{
	//	case OBJNAME::MONSTER:
	//	case OBJNAME::TILE:
	//	{
	//		deleteObj(this);
	//		// TODO 이펙트 생성
	//		break;
	//	}

	//	}
	//}
	//else if (OBJNAME::MISSILE_MONSTER == getName())
	//{	// 몬스터의 미사일인 경우
	//	switch (pOther->getOwner()->getName())
	//	{
	//	case OBJNAME::PLAYER:
	//	case OBJNAME::TILE:
	//	{
	//		deleteObj(this);
	//		// TODO 이펙트 생성
	//		break;
	//	}

	//	}
	//}
}
