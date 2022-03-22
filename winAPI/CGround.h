#pragma once
#include "CObject.h"
class CGround : public CObject
{

public:
	CGround();
	virtual ~CGround();

	virtual void update();
	virtual void render(HDC hDC);

	static CGround* create(float left, float top, float right, float bottom);

	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);
};

