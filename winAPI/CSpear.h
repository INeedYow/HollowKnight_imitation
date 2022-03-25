#pragma once
#include "CMissile.h"

class CTexture;

class CSpear : public CMissile
{
	float	m_fTheta;
	UINT	m_uiStep;		// 0 �ڷ� ������ + ���� // 1 ���� // 2 ��� // 3 �߻�
	float	m_fSpdMax;

	fPoint	m_fpHead;
	fVec2	m_fvDir;
public:
	CSpear();
	~CSpear();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);

	void setMaxSpd(float spd);
};

