#pragma once
#include "CMissile.h"

class CTexture;

class CSpear : public CMissile
{
	float	m_fTheta;
	UINT	m_uiStep;		// 0 뒤로 움직임 + 조준 // 1 조준 // 2 대기 // 3 발사
	float	m_fSpdMax;

public:
	CSpear();
	~CSpear();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);

	void setMaxSpd(float spd);
	//POINT* rotate(fPoint pos1, /*fPoint pos2, fPoint pos3,*/ float theta);
};

