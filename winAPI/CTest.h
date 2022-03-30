#pragma once
#include "CObject.h"
class CTest :    public CObject
{
	float m_fRad;
	bool m_bOn;
	
public:
	CTest();
	~CTest();

	virtual void update();
	virtual void render(HDC hDC);

	float getRad();

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);
};

