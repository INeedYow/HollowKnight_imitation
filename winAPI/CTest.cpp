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
	m_fRad = 100.f;
	m_fSpd = 2.f;
	m_fTheta = 0.f;
	setName(eOBJNAME::TEST);
	m_pOwner = nullptr;

	m_fRadius = 0.f;

	m_fpOffset = {};

	createCollider();
	getCollider()->setSize(fPoint(15.f, 15.f));
}

CTest::~CTest()
{
}

void CTest::update()
{

	fPoint ownerPos = m_pOwner->getPos();
	fPoint pos = getPos();

	if (KEY_HOLD('H'))
		m_fSpd += 1.f * fDT;
	if (KEY_HOLD('G'))
		m_fSpd -= 1.f * fDT;
	if (KEY_ON('J'))
		m_fSpd = 2.f;


	m_fTheta += m_fSpd * fDT;

	//if (m_fTheta > 6.3f)
	//	m_fTheta = 0.f;

	if (KEY_HOLD('U'))
		m_fRad += 70 * fDT;
	if (KEY_HOLD('I'))
		m_fRad -= 70 * fDT;
	if (KEY_ON('O'))
		m_fRad = m_fRadius;

	if (KEY_ON('T'))
		m_bRotRight = !m_bRotRight;

	if (m_bRotRight)
	{
		pos.x = (float)cos(m_fTheta) * m_fRad;
		pos.y = (float)sin(m_fTheta) * m_fRad;
	}
	else
	{
		pos.x = (float)sin(m_fTheta) * m_fRad;
		pos.y = (float)cos(m_fTheta) * m_fRad;
	}

	pos += ownerPos;

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

	float rad = (float)sqrt((double)(m_fpOffset.x * m_fpOffset.x) + 
							(double)(m_fpOffset.y * m_fpOffset.y));

	setRadius(rad);
}

void CTest::setRadius(float rad)
{
	m_fRadius = rad;
}

void CTest::collisionEnter(CCollider* pOther)
{
}