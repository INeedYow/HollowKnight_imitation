#pragma once
#include "CEffect.h"
class CEffect_Move : public CEffect
{
	float m_fSpd;
	float m_fDegree;
	float m_fDecel;

public:
	CEffect_Move();
	virtual ~CEffect_Move();

	virtual void update();
	virtual void render(HDC hDC);

	void setSpeed(float spd);
	void setDecel(float decel);
	void setDegree(float deg);
};
#define DEG2RAD(d)		d / 57.f;	