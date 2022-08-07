#include "framework.h"
#include "CWall.h"

CWall::CWall()
{
	setName(eOBJNAME::WALL);
	setPos(fPoint(1.f, 1.f));
	setSize(fPoint(1.f, 1.f));

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CWall::~CWall()
{
}

void CWall::update()
{
}

void CWall::render(HDC hDC)
{
	if (g_bDebug)
		componentRender(hDC);
}

void CWall::create(float left, float top, float right, float bottom)
{
	CWall* pNewWall = new CWall;
	pNewWall->setPos(fPoint((left + right) * 0.5f, (top + bottom) * 0.5f));
	pNewWall->getCollider()->setSize(fPoint(right - left, bottom - top));

	createObj(pNewWall, eOBJ::WALL);
}