#pragma once
#include "CObject.h"

class CTexture;

class CShield : public CObject
{
	CTexture* m_pTex;

	CObject* m_pOwner;

	float	m_fRadius;
	float	m_fSpd;
	float	m_fTheta;
	bool	m_bRotRight;

public:
	CShield();
	CShield(fPoint pos, CObject* pOwner);
	virtual ~CShield();
	virtual CShield* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void setRot(bool isRight);
	void setOwner(CObject* pOwner);
	void setfSpeed(float spd);
	void setRadius(float rad);			

	float getSpeed();
	float getRadius();

	void collisionEnter(CCollider* pOther);

	void calculateRad();
};
// TODO pos, owner ���� set���ְ� radius�� set����� �ϴµ� // �Ǽ� �����ϴ� �����?