#include "framework.h"
#include "CShield.h"

CShield::CShield()
{
	m_pTex = nullptr;

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(70.f, 70.f));
	setName(eOBJNAME::SHIELD);
	m_fSpd = 2.f;
	m_fTheta = 0.f;
	m_fRadius = 0.f;
	m_bRotRight = true;

	m_pOwner = nullptr;

	createCollider();
	getCollider()->setSize(fPoint(70.f, 70.f));

	//createAnimator();
}

CShield::CShield(fPoint pos, CObject* pOwner)
{
	setPos(pos);
	m_pOwner = pOwner;

	calculateRad();
}

CShield::~CShield()
{
}


CShield* CShield::clone()
{
	return new CShield(*this);
}

void CShield::calculateRad()
{
	float x = getPos().x - m_pOwner->getPos().x;
	float y = getPos().y - m_pOwner->getPos().y;

	m_fRadius = (float)sqrt((double)x * x + (double)y * y );
}

void CShield::update()
{
	;
	fPoint pos = getPos();

	m_fTheta += m_fSpd * fDT;

	if (m_bRotRight)
	{
		pos.x = m_fRadius * (float)cos(m_fTheta);
		pos.y = m_fRadius * (float)sin(m_fTheta);
	}
	else
	{
		pos.x = m_fRadius * (float)sin(m_fTheta);
		pos.y = m_fRadius * (float)cos(m_fTheta);
	}

	pos += m_pOwner->getPos();

	setPos(pos);

	//getAnimator()->update();
}

void CShield::render(HDC hDC)
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


void CShield::setRot(bool isRight)
{
	m_bRotRight = isRight;
}

void CShield::setOwner(CObject* pOwner)
{
	m_pOwner = pOwner;
}

void CShield::setfSpeed(float spd)
{
	m_fSpd = spd;
}

void CShield::setRadius(float rad)
{
	m_fRadius = rad;
}

float CShield::getSpeed()
{
	return m_fSpd;
}

float CShield::getRadius()
{
	return m_fRadius;
}

void CShield::collisionEnter(CCollider* pOther)
{
}
