#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	fVec2 m_fvDir;
	float m_fSpeed;

public:
	CMissile();
	~CMissile();
	virtual CMissile* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void setDir(fVec2 vec);
	void setDir(float theta);

	void collisionEnter(CCollider* pOther);
};

