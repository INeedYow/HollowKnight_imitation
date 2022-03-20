#pragma once
#include "CObject.h"
class CGround : public CObject
{

public:
	CGround();
	virtual ~CGround();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);
};

