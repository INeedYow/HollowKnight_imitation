#pragma once
#include "CObject.h"
class CGround : public CObject
{

public:
	CGround();
	virtual ~CGround();

	virtual void update();
	virtual void render(HDC hDC);

	static void create(float left, float top, float right, float bottom);
};

