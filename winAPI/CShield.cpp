#include "framework.h"
#include "CShield.h"
#include "CTexture.h"

#include "SelectGDI.h"

CShield::CShield()
{
	m_pTex = nullptr;

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(70.f, 70.f));
	setName(eOBJNAME::SHIELD);
	m_fSpd = 2.5f;
	m_fTheta = 0.f;
	m_fRadius = 0.f;
	m_bRotRight = true;

	m_pOwner = nullptr;

	createCollider();
	getCollider()->setSize(fPoint(70.f, 70.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();
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

	m_fRadius = (float)sqrt((double)x * x + (double)y * y);
}

void CShield::update()
{
	fPoint pos = getPos();

	if (m_bRotRight)
	{
		m_fTheta += m_fSpd * fDT;
	}
	else
	{
		m_fTheta -= m_fSpd * fDT;
	}
	
	if (m_fTheta > 2 * PI)
	{
		m_fTheta = 0.f;
		//m_pTex->setRotatedBitmap(m_fRadius, RGB(255, 0, 255));
	}
	

	pos.x = m_fRadius * (float)cos(m_fTheta);
	pos.y = m_fRadius * (float)sin(m_fTheta);

	pos += m_pOwner->getPos();

	setPos(pos);
	
	getAnimator()->update();
}

void CShield::render(HDC hDC)
{
	componentRender(hDC);
}


void CShield::setRot(bool isRight)
{
	m_bRotRight = isRight;
}

void CShield::toggleRot()
{
	m_bRotRight = !m_bRotRight;
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

void CShield::setTheta(float theta)
{
	m_fTheta = theta;
}

void CShield::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
}

CTexture* CShield::getTex()
{
	return m_pTex;
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
