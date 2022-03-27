#pragma once
#include "CObject.h"
class CWall : public CObject
{

public:
	CWall();
	virtual ~CWall();

	virtual void update();
	virtual void render(HDC hDC);

	static void create(float left, float top, float right, float bottom);
};

