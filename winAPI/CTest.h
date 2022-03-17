#pragma once
#include "CObject.h"
class CTest :
    public CObject
{
private:

	CObject* m_pOwner;
	fPoint	m_fpOffset;

	fVec2	m_fvDir;
	float	m_fSpeed;
	float	m_fTimer;
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
};

