#include "framework.h"
#include "CEffect_Move.h"

CEffect_Move::CEffect_Move()
{
	createAnimator();
	m_fSpd = 0.f;
	m_fDegree = 0.f;
	m_fDecel = 0.f;
	
}

CEffect_Move::~CEffect_Move()
{
}

void CEffect_Move::update()
{
	CEffect::update();

	if (getDuration() < 1.3f)
	{
		PLAY(L"dream_disapear");
	}

	fPoint pos = getPos();

	float t = DEG2RAD(m_fDegree);

	pos.x += (float)(sin(t) * m_fSpd * fDT);
	pos.y += (float)(cos(t) * m_fSpd * fDT);

	m_fSpd -= m_fDecel * fDT;

	if (m_fSpd < 0.f)
		m_fSpd = 0.f;

	setPos(pos);
}

void CEffect_Move::render(HDC hDC)
{
	componentRender(hDC);
}

void CEffect_Move::setSpeed(float spd)
{
	m_fSpd = spd;
}

void CEffect_Move::setDecel(float decel)
{
	m_fDecel = decel;
}

void CEffect_Move::setDegree(float theta)
{
	m_fDegree = theta;
}
