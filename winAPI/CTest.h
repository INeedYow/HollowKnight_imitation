#pragma once
#include "CObject.h"
class CTest :
    public CObject
{
private:
	CObject* m_pOwner;
	fPoint	m_fpOffset;

	float	m_fRadius;

	fVec2	m_fvDir;
	float	m_fRad;
	float	m_fSpd;
	float	m_fTheta;
	bool	m_bRotRight;

public:
	CTest();
	~CTest();
	virtual CTest* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void setDir(fVec2 vec);
	void setDir(float theta);
	void setRot(bool isRight);
	void setOwner(CObject* pOwner);
	void setOffset(fPoint offset);

	void collisionEnter(CCollider* pOther);

private:
	void setRadius(float rad);
	
};

